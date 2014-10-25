#pragma once
#include <string>
#include "../MapFile/Compression/Base64.hpp"
#include "sha1.h"
#include "../../Log.hpp"
#include "INIFile.hpp"
#include "INISection.hpp"

class DigestClass
{
public:

	static std::string getCustomDigestFor(INIFile* file, bool writeLock = false)
	{
		const static int HASHSIZE = 20; //Always allocates 20 bytes

		return base64_encode(generateINIDigest(file, writeLock), HASHSIZE);

		return std::string();
	}

	static bool isLocked(INIFile* file)
	{
		auto digest = file->getDigest();

		if (!digest.empty())
		{
			std::string toCompareLock = std::move(getCustomDigestFor(file, 1));

			clearChecksumIntegers();

			if (toCompareLock == digest)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			Log::line("Checking for write lock, Digest section is missing!", Log::DEBUG);
		}
		return false;
	}

	static bool validateDigest(INIFile* file, const std::string& name)
	{
		std::string toCompare = std::move(getCustomDigestFor(file));
		std::string lockCompare = std::move(getCustomDigestFor(file, true));
		
		clearChecksumIntegers();

		auto digest = file->getDigest();
		if (digest.empty())
		{
			Log::line("File with name '" + name + "' is supposed to have a valid Digest, but it doesn't exist. File is not authentic!", Log::DEBUG);
			return false;
		}
		else
		{
			std::string original = std::move(digest);
			if (original == toCompare)
			{
				Log::line("Digest is correct and matches file with name '" + name + "'. File is authentic!", Log::DEBUG);
				return true;
			}
			else if (original == lockCompare)
			{
				Log::line("Digest indicates file with path '"+ name + "' is locked for writing. The editor will not modify it. File is authentic!", Log::DEBUG);
				return true;
			}
			else if (original != toCompare && original != lockCompare)
			{
				Log::line("Digest is incorrect and does not match file with name '" + name + "' (this file has been tampered with). File is not authentic!", Log::DEBUG);
				return false;
			}
		}
		return false;
	}

	static void clearChecksumIntegers()
	{
		sections = -1;
		keysLen = -1;
		valuesLen = -1;
	}

private:
	static int sections;
	static int keysLen;
	static int valuesLen;

	static byte* generateINIDigest(INIFile* ini, bool writeLock)
	{
		const static size_t LEN = 64;
		std::vector<byte> footer(LEN);
	
		if (keysLen == -1)
			keysLen = ini->generateAndGetCheckSum(0);
		auto first = reinterpret_cast<byte*>(&keysLen);
		footer[0] = first[0]; footer[1] = first[1]; footer[2] = first[2]; footer[3] = first[3];

		if (valuesLen == -1)
			valuesLen = ini->generateAndGetCheckSum(1);
		auto second = reinterpret_cast<byte*>(&valuesLen);
		footer[4] = second[0]; footer[5] = second[1]; footer[6] = second[2]; footer[7] = second[3];

		if (sections == -1)
			sections = ini->getSectionCountWithoutDigest() * 0x186A0;
		auto third = reinterpret_cast<byte*>(&sections);
		footer[8] = third[0]; footer[9] = third[1]; footer[10] = third[2]; footer[11] = third[3];

		if (writeLock)
			footer[12] = 0xFF;

		SHA1 sha;

		byte* digested = sha.getDigest(&footer[0], LEN);

		return digested;
	}
};