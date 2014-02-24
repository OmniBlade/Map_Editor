/*
 * BinaryReader.cpp
 *
 *  Created on: 12 feb. 2014
 *      Author: Rik
 *	  Semester: CAR
 */

#include "stdafx.h"
#include "../GlobalData.hpp"
#include "BinaryReader.hpp"
#include <cstring>
#include <iostream>
#include <algorithm>


BinaryReader::BinaryReader(const std::string& _fullFileName)
{
	fullFileName = _fullFileName;
	fileStream.open(_fullFileName, std::ios::in | std::ios::binary);
	if (fileStream.is_open())
	{
		isOpened = true;
	}
	else
	{
		std::cout << "Unable to open MIX with path: " << _fullFileName << std::endl;
	}
}

BinaryReader::~BinaryReader()
{
	isOpened = false;
	fileStream.close();
}

void BinaryReader::setOffset(int _offset)
{
	std::cout << "Setting offset to: " << _offset << std::endl;
	fileStream.seekg(_offset);
}

int BinaryReader::getOffset()
{
	return fileStream.tellg();
}

unsigned int BinaryReader::readUInt(bool isBigEndian /* = false */)
{
	unsigned int theInt = 0;
	fileStream.read(reinterpret_cast<char*>(&theInt), sizeof(unsigned int));

	if(isBigEndian)
		return littleToBigUInt(theInt);
	else
		return theInt;
}

int BinaryReader::readInt(bool isBigEndian /* = false */)
{
	int theInt = 0;
	fileStream.read(reinterpret_cast<char*>(&theInt), sizeof(int));

	if(isBigEndian)
		return littleToBigInt(theInt);
	else
		return theInt;
}

unsigned short BinaryReader::readUShort(bool isBigEndian /* = false */)
{
	unsigned short theShort = 0;
	fileStream.read(reinterpret_cast<char*>(&theShort), sizeof(unsigned short));

	if(isBigEndian)
		return littleToBigUShort(theShort);
	else
		return theShort;
}

short BinaryReader::readShort(bool isBigEndian /* = false */)
{
	short theShort = 0;
	fileStream.read(reinterpret_cast<char*>(&theShort), sizeof(short));

	if(isBigEndian)
		return littleToBigShort(theShort);
	else
		return theShort;
}

byte BinaryReader::readByte()
{
	byte aByte;
	fileStream.read(reinterpret_cast<char*>(&aByte), sizeof(char));

	return aByte;
}

void BinaryReader::discardBytes(unsigned int amount)
{
	std::vector<byte> buffer(amount);
	for(unsigned int i = 0; i < amount; ++i)
	{
		byte aByte;
		fileStream.read(reinterpret_cast<char*>(&aByte), sizeof(char));
	}
}

std::vector<byte> BinaryReader::readByteBlock(unsigned int amountOfBytes)
{
	std::vector<byte> buffer(amountOfBytes);
	fileStream.read(reinterpret_cast<char*>(&buffer[0]), amountOfBytes);
	return buffer;
 }

std::string BinaryReader::readTextLine()
{
	std::string theLine;
	if (std::getline(fileStream, theLine))
		return theLine;
	else
		return "";
}

bool BinaryReader::checkEOF()
{
	if (fileStream.eof())
		return true;
	else
		return false;
}

unsigned short BinaryReader::littleToBigUShort(unsigned short toSwap)
{
	byte* src = reinterpret_cast<byte*>(&toSwap);
	short ret;
	byte* dest = reinterpret_cast<byte*>(&ret);
	dest[0] = src[1];
	dest[1] = src[0];

	return ret;
}

short BinaryReader::littleToBigShort(short toSwap)
{
	byte* src = reinterpret_cast<byte*>(&toSwap);
	short ret;
	byte* dest = reinterpret_cast<byte*>(&ret);
	dest[0] = src[1];
	dest[1] = src[0];

	return ret;
}

unsigned int BinaryReader::littleToBigUInt(unsigned int toSwap)
{
	byte* src = reinterpret_cast<byte*>(&toSwap);
	unsigned int ret;
	byte* dest = reinterpret_cast<byte*>(&ret);
	dest[0] = src[3];
	dest[1] = src[2];
	dest[2] = src[1];
	dest[3] = src[0];

	return ret;
}

int BinaryReader::littleToBigInt(int toSwap)
{
	byte* src = reinterpret_cast<byte*>(&toSwap);
	int ret;
	byte* dest = reinterpret_cast<byte*>(&ret);
	dest[0] = src[3];
	dest[1] = src[2];
	dest[2] = src[1];
	dest[3] = src[0];

	return ret;
}

std::vector<byte> BinaryReader::readByteBlockFromOffset(__int32 offset, unsigned int amountOfBytes)
{
	std::vector<byte> byteBuffer(amountOfBytes);
	fileStream.seekg(offset);
	fileStream.read(reinterpret_cast<char*>(&byteBuffer[0]), amountOfBytes);
	return byteBuffer;
}
