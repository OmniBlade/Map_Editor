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
private:
	bool atEOF = false;
	int fileSize = 0, offset = 0;
	std::string fullFileName;
	//int startingOffset = 0;
	std::ifstream fileStream;

public:
	/*
		Opens the file as a binary file and opens a file stream to it
		@param _fullFileName The full path to the file
		@param logError Should the logger log an error if the file cannot be opened?
	*/
	BinaryReader(const std::string& _fullFileName, bool logError = true);// , __int32 _offset = 0, int size = 0);
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
	
	/*
		Sets the size of the file to the value given in the parameter
		@param _size The new size of the file
	*/
	void setSize(int _size);
	
	/*
		Returns the file size 
		@return Size of the file as integer
	*/
	int getFileSize();
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
		Reads an amount of byte from the file
	*/
	void readBlock(void* ptr, size_t length) { fileStream.read(reinterpret_cast<char*>(ptr), length); }
	/*
	Reads a single signed char from the file
	*/
	char readChar()
	{
		char aChar = 0;
		fileStream.read(reinterpret_cast<char*>(&aChar), sizeof(char));

		return aChar;
	};
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
		Reads a single wstring line
	*/
	std::wstring readWTextLine(int length) { std::wstring ret; ret.resize(length*2);  readBlock(&ret[0], length*2); return ret; };

	/*
		Checks whether the file is at eof, returns true if it is, false if it isn't
	*/
	bool checkEOF();

	/*
		Returns the instance of this class as a const
		@return The pointer to the instance of this class
	*/
	const BinaryReader* get() const;

	//Endian conversion
	/*
		Trivial, these functions convert values from little to big endian and vice versa
	*/
	unsigned short littleToBigUShort(unsigned short toSwap);
	short littleToBigShort(short toSwap);
	unsigned int littleToBigUInt(unsigned int toSwap);
	int littleToBigInt(int toSwap);

	/* Gets the size of the file */
	//int getFileSize();

	bool isOpened = false;
};

#endif /* BINARYREADER_HPP_ */

