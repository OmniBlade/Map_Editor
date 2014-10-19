#pragma once
#include <string>
#include "../MapFile/Base64.hpp"
#include "sha1.h"
#include "../../Log.hpp"
#include "INIFile.hpp"
#include "INISection.hpp"

class DigestClass
{
public:
	static std::string getCustomDigestFor(INIFile* file)
	{
		const static int HASHSIZE = 20; //Always allocates 20 bytes

		return base64_encode(generateINIDigest(file), HASHSIZE);

		return std::string();
	}

	static bool validateDigest(INIFile* file, const std::string& name)
	{
		std::string toCompare = std::move(getCustomDigestFor(file));
		
		auto section = file->getSection("Digest");
		if (!section)
		{
			Log::line("File with name '" + name + "' is supposed to have a valid Digest, but it doesn't exist. File is not authentic!", Log::DEBUG);
			return false;
		}
		else
		{
			std::string original = std::move(section->getValue(section->getKey(0)));
			if (original == toCompare)
			{
				Log::line("Digest is correct and matches file with name '" + name + "'. File is authentic!", Log::DEBUG);
				return true;
			}
			else
			{
				Log::line("Digest is incorrect and does not match file with name '" + name + "' (this file has been tampered with). File is not authentic!", Log::DEBUG);
				return false;
			}
		}
		return false;
	}

private:
	static byte* generateINIDigest(INIFile* ini)
	{
		const static size_t LEN = 64;
		std::vector<byte> footer(LEN);
	
		//int sections = ini->getSectionCount() * 0x186A0;
		int sections = ini->getSectionCount() * 0x186A0;
		int keysLen = ini->generateAndGetCheckSum(0);
		int valuesLen = ini->generateAndGetCheckSum(1);

		auto first = reinterpret_cast<byte*>(&keysLen);
		footer[0] = first[0]; footer[1] = first[1]; footer[2] = first[2]; footer[3] = first[3];

		auto second = reinterpret_cast<byte*>(&valuesLen);
		footer[4] = second[0]; footer[5] = second[1]; footer[6] = second[2]; footer[7] = second[3];
			
		auto third = reinterpret_cast<byte*>(&sections);
		footer[8] = third[0]; footer[9] = third[1]; footer[10] = third[2]; footer[11] = third[3];

		SHA1 sha;

		byte* digested = sha.getDigest(&footer[0], LEN);

		return digested;
	}
};