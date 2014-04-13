/*
 * BinaryReader.cpp
 *
 *  Created on: 12 feb. 2014
 *      Author: Rik
 *	  Semester: CAR
 */

#include "stdafx.h"
#include "../../Config.hpp"
#include "BinaryReader.hpp"
#include "../../Log.hpp"
#include <cstring>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <share.h>
#include <stdio.h>


BinaryReader::BinaryReader(const std::string& _fullFileName)//, __int32 _offset, int size)
:fullFileName(_fullFileName)
{
	fileStream.open(_fullFileName, std::ios::in | std::ios::binary, _SH_DENYNO);

	fileStream.seekg(0, std::ios::end);
	fileSize = (int) fileStream.tellg();
	fileStream.seekg(0, std::ios::beg);
	
	//std::cout << "Size: " << fileSize << " Offset: " << _offset << std::endl;
	if (fileStream.is_open())
	{
		isOpened = true;
		//std::cout << "File: " << _fullFileName << " is opened.\nSize is: " << fileSize << std::endl;
	}
	else
	{
		Log::line("Unable to open file with path: " + _fullFileName, Log::WARNING);
	}
}


BinaryReader::BinaryReader(std::ifstream* _fileStream)
{
	//fileStream = _fileStream;
}

BinaryReader::~BinaryReader()
{
	isOpened = false;
	//fclose(theFile);
	fileStream.close();
}

void BinaryReader::setOffset(int _offset)
{
	//std::cout << "Setting offset to: " << _offset << std::endl;
	fileStream.seekg(_offset);
	offset = _offset;
	//fseek(theFile, _offset, SEEK_SET);
}

int BinaryReader::getOffset()
{
	//return ftell(theFile);
	return (int) fileStream.tellg();
}

void BinaryReader::setSize(int _size)
{
	fileSize = _size;
}

int BinaryReader::getFileSize()
{
	return fileSize;
}

unsigned int BinaryReader::readUInt(bool isBigEndian /* = false */)
{
	unsigned int theInt = 0;
	//fgets(reinterpret_cast<char*>(&theInt), sizeof(int), theFile);
	fileStream.read(reinterpret_cast<char*>(&theInt), sizeof(unsigned int));

	if(isBigEndian)
		return littleToBigUInt(theInt);
	else
		return theInt;
}

int BinaryReader::readInt(bool isBigEndian /* = false */)
{
	int theInt = 0;
	//fgets(reinterpret_cast<char*>(&theInt), sizeof(int), theFile);
	fileStream.read(reinterpret_cast<char*>(&theInt), sizeof(int));

	if(isBigEndian)
		return littleToBigInt(theInt);
	else
		return theInt;
}

unsigned short BinaryReader::readUShort(bool isBigEndian /* = false */)
{
	unsigned short theShort = 0;
	//fgets(reinterpret_cast<char*>(&theShort), sizeof(short), theFile);
	fileStream.read(reinterpret_cast<char*>(&theShort), sizeof(unsigned short));

	if(isBigEndian)
		return littleToBigUShort(theShort);
	else
		return theShort;
}

short BinaryReader::readShort(bool isBigEndian /* = false */)
{
	short theShort = 0;
	//fgets(reinterpret_cast<char*>(&theShort), sizeof(short), theFile);
	fileStream.read(reinterpret_cast<char*>(&theShort), sizeof(short));

	if(isBigEndian)
		return littleToBigShort(theShort);
	else
		return theShort;
}

byte BinaryReader::readByte()
{
	byte aByte;
	//fgets(reinterpret_cast<char*>(&aByte), sizeof(byte), theFile);
	fileStream.read(reinterpret_cast<char*>(&aByte), sizeof(char));

	return aByte;
}

char BinaryReader::readChar()
{
	char aChar = 0;
	//fgets(reinterpret_cast<char*>(&aByte), sizeof(byte), theFile);
	fileStream.read(reinterpret_cast<char*>(&aChar), sizeof(char));

	return aChar;
}

void BinaryReader::discardBytes(unsigned int amount)
{
	std::vector<byte> buffer(amount);
	for(unsigned int i = 0; i < amount; ++i)
	{
		byte aByte;
		//fgets(reinterpret_cast<char*>(&aByte), sizeof(byte), theFile);
		fileStream.read(reinterpret_cast<char*>(&aByte), sizeof(char));
	}
}

std::vector<byte> BinaryReader::readByteBlock(unsigned int amountOfBytes)
{
	std::vector<byte> buffer(amountOfBytes);
	if (amountOfBytes == 0)
		return buffer;
	//fgets(reinterpret_cast<char*>(&buffer[0]), amountOfBytes, theFile); 
	fileStream.read(reinterpret_cast<char*>(&buffer[0]), amountOfBytes);
	return buffer;
}

std::string BinaryReader::readTextLine()
{
	char line [512] = "";

	for (unsigned int i = 0; i < 510; ++i)
	{
		char reatByte = readChar();
		line[i] = reatByte;
		if (line[i] == '\n' || line[i] == '\0' || line[i] == '\r')
		{
			line[i] = '\0';
		//	std::cout << "N, 0 or R!" << std::endl;
			return line;
		}
		/*else if (line[i] == EOF)
		{
			atEOF = true;
		//	std::cout << "EOF!" << std::endl;
			line[i] = '\0';
			return line;
		}*/
	}
	Log::line("The read line is longer than 511 characters, everything else will be discarded.", Log::ERRORS);
	//std::cout << "The line: " << line << std::endl;
	//auto isEnd = [](byte value) { return value == '\0' || value == '\n' || value == EOF; };

	bool endReached = false;
	while (endReached == false)
	{
		char currentChar = readChar();

		switch (currentChar)
		{
		case '\n':
		case EOF:
		case '\0':
		case '\r': 
			endReached = true;
		}
	}
	line[511] = '\0';
	return line;
}

bool BinaryReader::checkEOF()
{
	if (fileStream.tellg() >= offset + fileSize || fileStream.tellg() < 0)
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

std::vector<byte> BinaryReader::readByteBlockFromOffset(__int32 _offset, unsigned int amountOfBytes)
{
	std::vector<byte> byteBuffer(amountOfBytes);
	if (amountOfBytes == 0)
		return byteBuffer;

	fileStream.seekg(_offset);
	fileStream.read(reinterpret_cast<char*>(&byteBuffer[0]), amountOfBytes);

	return byteBuffer;
}