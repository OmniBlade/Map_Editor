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

	PackType(INISection* packSection, Type = Type::UNKNOWN);
	~PackType();


	/*
		== Decompression ==
	*/
	void decompress();
	
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
	void compress();
	void compressLZO();
	void compressF80();

	void encode64();
	/* Decodes the INISection* provided, automatically sets readSrc */
	void decode64();

	void setWriteSrc(const std::vector<byte>& bytes) { this->writeSrc = bytes; };
	std::vector<byte>& getWriteDest() { return writeDest; };
	void setReadSrc(const std::vector<byte>& bytes) { this->readSrc = bytes; };
	std::vector<byte>& getReadDest() { return readDest; };

	std::string getEncodedString() { return this->encoded64; };
	void clearEncodedString() { this->encoded64.clear(); };

private:
	INISection* packSection;
	std::vector<byte> readSrc, readDest, writeSrc, writeDest;
	std::string encoded64;
	Type compression;
	int srcIndex, destIndex;

};

