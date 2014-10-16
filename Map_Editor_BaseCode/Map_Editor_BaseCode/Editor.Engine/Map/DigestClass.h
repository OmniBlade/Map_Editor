#pragma once
#include <string>
#include "../../Editor.FileSystem/MapFile/Base64.hpp"
#include "../../Editor.FileSystem/MapFile/sha1.h"
#include "../../Editor.FileSystem/INIFile/INIFile.hpp"

class DigestClass
{
public:
	static void writeToINI(INIFile& file)
	{
		//Random so we call it here! :D
		file.SetValue("Digest", "1", getDigestBase64());
	}

	/*
		TODO: Find a purpose ~ Agent from the Matrix
	*/
	static void parse(const std::string& hash)
	{
		DigestClass::readHash = hash;
	}

private:
	static byte* getDigest(byte* toDigest = nullptr, size_t size = 0)
	{
		SHA1 sha;
		
		if (size > 0)
		{
			sha.addBytes(reinterpret_cast<char*>(toDigest), size);
		}

		byte* digested = sha.getDigest();

		return digested;
	}

	static std::string getDigestBase64(byte* toDigest = nullptr, size_t size = 0)
	{
		const static int HASHSIZE = 20; //Always allocates 20 bytes
		byte* digested = getDigest(toDigest, size);

		return base64_encode(digested, HASHSIZE);
	}

	static std::string readHash;
};