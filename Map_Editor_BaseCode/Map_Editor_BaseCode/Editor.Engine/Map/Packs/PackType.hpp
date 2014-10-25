#pragma once
#include <vector>
#include <string>

class INISection;

class PackType
{
public:
	/*
		There are two types of compressions available, Format80 and LZO
	*/
	enum Type
	{
		LZO = 0,
		F80 = 1,
		UNKNOWN = 2,
	};

	PackType(Type = Type::UNKNOWN);
	~PackType();

	/*
		== Decompression ==
	*/
	void decompress(byte* src, size_t src_len);
		
	/*
		== Compression ==
	*/
	void compress(byte* src, size_t src_len);

	std::vector<byte>& getWriteDest() { return writeDest; };
	std::vector<byte>& getReadDest() { return readDest; };
	void clearReadDest() { readDest.clear(); };
	void clearWriteDest() { writeDest.clear(); };

	std::string getEncodedString() { return this->encoded64; };
	void clearEncodedString() { this->encoded64.clear(); };

private:
	std::vector<byte> readDest, writeDest;
	std::string encoded64;
	Type compression;
	const static int F80_MAX = 262144;

};

