#pragma once
#include <string>
#include "../MapFile/Base64.hpp"
#include "../MapFile/sha1.h"
#include "../../Log.hpp"

class DigestClass
{
public:
	static std::string getRandomDigest()
	{
		return getDigestBase64();
	}

	static std::string getDigestForBytes(byte* bytes, size_t size)
	{
		if (size == 0 || !bytes)
		{
			Log::line("Unable to create a valid Digest value for the specified bytes, they don't exist! Returning a random Digest.", Log::DEBUG);
		}
		
		return getDigestBase64(bytes, size);
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