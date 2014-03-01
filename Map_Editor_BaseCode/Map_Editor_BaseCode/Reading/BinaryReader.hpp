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
#include <cstdio>

class BinaryReader {
public:
	/*
		Opens the file as a binary file and opens a file stream to it
		@param _fullFileName The full path to the file
	*/
	BinaryReader(const std::string& _fullFileName, __int32 _offset = 0, int size = 0);
	/*
		Creates a binary reader with a referenced file stream used by another
		@param _fileStream The 'file' from a parent that holds the file needed
	*/
	BinaryReader(std::ifstream* _fileStream);
	/*
		Upon destruction the reader closes the file too
	*/
	~BinaryReader();
	/*
		Sets the offset from the filestream to the specified value
		@param _offset The offset that will be set
	*/
	void setOffset(int _offset);
	/*
		Reads and returns the current offset
		@return The current offset from the file
	*/
	int getOffset();

	//Integers
	/*
		Reads an unsigned integer from the file
	*/
	unsigned int readUInt(bool isBigEndian = false);
	/*
		Reads a signed integer from the file
	*/
	int readInt(bool isBigEndian = false);
	//Shorts
	/*
		Reads an unsigned short from the file
	*/
	unsigned short readUShort(bool isBigEndian = false);
	/*
		Reads a signed short from the file
	*/
	short readShort(bool isBigEndian = false);
	//Bytes
	/*
		Reads a single byte from the file
	*/
	byte readByte();
	/*
	Reads a single signed char from the file
	*/
	char readChar();
	/*
		Kind of obsolete, skips the amount of bytes given
		@param amount The amount of bytes to skip
	*/
	void discardBytes(unsigned int amount);
	/*
		Reads a series of bytes from the current position of the filestream
		@param amountOfBytes The amount of bytes to read out
	*/
	std::vector<byte> readByteBlock(unsigned int amountOfBytes);
	/*
		Reads a series of bytes from the specified offset
		@param offset The offset to start reading from
		@param amountOfBytes The amount of bytes to read out
	*/
	std::vector<byte> readByteBlockFromOffset(__int32 offset, unsigned int amountOfBytes);
	/*
		Reads a single line until 'new line' character is found, mainly used for text files
	*/
	std::string readTextLine();
	/*
		Checks whether the file is at eof, returns true if it is, false if it isn't
	*/
	bool checkEOF();

	//Endian conversion
	/*
		Trivial, these functions convert values from little to big endian and vice versa
	*/
	unsigned short littleToBigUShort(unsigned short toSwap);
	short littleToBigShort(short toSwap);
	unsigned int littleToBigUInt(unsigned int toSwap);
	int littleToBigInt(int toSwap);

	/* Gets the filestream */
	//FILE* getFileStream();

private:
	bool isOpened = false, atEOF = false;
	int fileSize = 0 , offset = 0;
	std::string fullFileName;
	//int startingOffset = 0;
	std::ifstream fileStream;
};

#endif /* BINARYREADER_HPP_ */

