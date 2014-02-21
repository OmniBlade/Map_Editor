/*
 * BinaryReader.hpp
 *
 *  Created on: 12 feb. 2014
 *      Author: Rik
 *	  Semester: CAR
 */

#ifndef BINARYREADER_HPP_
#define BINARYREADER_HPP_

//#include "../Handlers/MixFileHandler.hpp"
#include <fstream>
#include <vector>
#include <string>

class BinaryReader {
public:
	BinaryReader(const std::string& fileName);
	BinaryReader(int _startingOffset);
	~BinaryReader();
	void setOffset(int _offset);
	void setStartingOffset(int _offset);
	int getOffset();
	void restoreOffset();
	void resetOffset();
	//Integers
	unsigned int readUInt(bool isBigEndian = false);
	int readInt(bool isBigEndian = false);
	//Shorts
	unsigned short readUShort(bool isBigEndian = false);
	short readShort(bool isBigEndian = false);
	//Bytes
	byte readByte();
	void discardBytes(unsigned int amount);
	std::vector<byte> readByteBlock(unsigned int amountOfBytes);
	std::vector<byte> readByteBlockFromOffset(const std::string& fullFileName, __int32 offset, unsigned int amountOfBytes);
	//Endian conversion
	unsigned short littleToBigUShort(unsigned short toSwap);
	short littleToBigShort(short toSwap);
	unsigned int littleToBigUInt(unsigned int toSwap);
	int littleToBigInt(int toSwap);

private:
	bool isOpened = false;
	std::string fullFileName;
	int startingOffset = 0;
	int previousOffset = 0;
	std::ifstream fileStream;

};

#endif /* BINARYREADER_HPP_ */

