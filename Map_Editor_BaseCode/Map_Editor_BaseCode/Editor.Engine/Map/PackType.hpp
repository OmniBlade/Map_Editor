#pragma once
#include <vector>

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

	PackType(INISection* packSection, Type = Type::UNKNOWN);
	~PackType();


	/*
		== Decompression ==
	*/
	void decompress();
	std::vector<byte>& getDest() { return dest; };
	
	/*
		Decompresses a LZO compressed section
	*/
	void decompressLZO();

	/*
		Decompresses a Format80 compressed section
	*/
	void decompressF80();
	
	/*
		== Compression ==
	*/
	void encode64();

private:
	INISection* packSection;
	std::vector<byte> src, dest;
	Type compression;
	int srcIndex, destIndex;

};

