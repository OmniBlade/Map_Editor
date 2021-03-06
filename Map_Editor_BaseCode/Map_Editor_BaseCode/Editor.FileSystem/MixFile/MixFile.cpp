/*
 * MixFile.cpp
 *
 *  Created on: 12 feb. 2014
 *      Author: Rik
 *	  Semester: CAR
 */

#include "stdafx.h"
#include "MixFile.hpp"
#include "../FileManager/BinaryReader.hpp"
#include "KeyCalculator.hpp"
#include "Blowfish.hpp"
#include "Ccrc.hpp"
#include "../../Config.hpp"
#include <cstring>
#include <algorithm>
#include <iostream>

//PARENT
MixFile::MixFile(const std::string& _name, MixFile* _parent, int fileID)
: mixName(_name), parent(_parent)
{
	std::cout << "MixFile values, Name: " << _name << " Parent: " << _parent << " fileID: " << fileID << std::endl;
	if (_parent != nullptr)
	{
		startingOffset = _parent->getAFileOffset(fileID);
		std::cout << "Starting offset from parent: " << startingOffset << std::endl;
	}
	determineMixReader();
	mixReader->setOffset(startingOffset);
	handleHeader();
	dumpIndex();
}

MixFile::MixFile(BinaryReader* _mixReader, int offset, int size, const std::string& _mixName)
:mixReader(_mixReader), mixName(_mixName)
{
	mixReader->setOffset(offset);
	mixReader->setSize(size);
	handleHeader();
}

void MixFile::handleHeader()
{
	//::cout << "Current offset at header start: " << mixReader->getOffset() << std::endl;
	unsigned short possibleCount = mixReader->readUShort();

	if (possibleCount != 0)
	{
		//std::cout << "V1" << std::endl;
		readTDHeader(possibleCount);
		//Set offset to the start of body
		bodyOffset = mixReader->getOffset() - startingOffset;
	}
	else if (possibleCount == 0)
	{
		//std::cout << "V2";
		unsigned short flags = mixReader->readUShort();
		if ((flags & 2) == 0) //Durr
		{
			//std::cout << " Unencrypted" << std::endl;
			//Need to read out the files because TD header takes filecount as a parameter
			unsigned short fileCount = mixReader->readUShort();
			readTDHeader(fileCount);
			//Set offset to the start of body
			bodyOffset = mixReader->getOffset() - startingOffset;
		}
		else if ((flags & 2) != 0) //2 is the identifier for Encryption
		{
			//std::cout << " Encrypted" << std::endl;
			readRAHeader();
			//Set offset to the start of body
			bodyOffset = mixReader->getOffset() - startingOffset;
			//((((12 * mixIndex.size()) + 7) / 8) * 8) + 
		}
	}
	else
	{
		std::cout << "Unable to determine MIX Version!" << std::endl;
	}

	//std::cout << "Body offset after header reading: " << bodyOffset << std::endl;
}

void MixFile::readTDHeader(unsigned short fileCount)
{
	header.files = fileCount;
	header.size = mixReader->readUInt();

	std::vector<t_mix_index_header> files(header.files);
	auto item_buffer = mixReader->readByteBlock(header.files * sizeof(t_mix_index_header));
	for (int i = 0; i < header.files; ++i)
	{
		files[i] = reinterpret_cast<t_mix_index_header*>(&item_buffer[0])[i];
	}
	mixIndex = files;

	//std::cout << "Files: " << header.files << std::endl;
}

void MixFile::readRAHeader()
{
	std::vector<byte> encryptionBytes = mixReader->readByteBlock(80);

	byte key[56];
	get_blowfish_key(encryptionBytes.data(), key);
	Blowfish blowfish;

	blowfish.set_key(key, 56);
	std::vector<byte> toByte = mixReader->readByteBlock(8);
	byte* pE = &toByte[0];
	blowfish.decipher(pE, pE, 8);

	memcpy(&header, pE, sizeof(t_mix_header));

	int c_files = header.files;
	const int cb_index = c_files * sizeof(t_mix_index_header);
	const int cb_f = (cb_index + 5) & ~7;

	auto file_buffer = mixReader->readByteBlock(cb_f);
	blowfish.decipher(file_buffer.data(), &file_buffer[0], cb_f);
	std::vector<t_mix_index_header> files(header.files);
	memcpy(reinterpret_cast<byte*>(&files[0]), &pE[6], 2);
	memcpy(reinterpret_cast<byte*>(&files[0]) + 2, &file_buffer[0], (cb_index - 2));

	mixIndex = files;
	//std::cout << "Files: " << files.size() << std::endl;
}

std::string MixFile::getUpperParentName()
{
	if (parent == nullptr)
	{
		return mixName;
	}
	else
	{
		MixFile* theMix = this;
		while (true)
		{
			theMix = theMix->parent;
			if (theMix->parent == nullptr)
			{
				return theMix->mixName;
			}
		}
	}
	return "";
}


bool MixFile::checkFileExistance(__int32 fileID)
{
	for (unsigned int i = 0; i < mixIndex.size(); ++i)
	{
		if (mixIndex[i].id == fileID)
			return true;
	}
	return false;
}

int MixFile::getAFileOffset(__int32 fileID)
{
	for (unsigned int i = 0; i < mixIndex.size(); ++i)
	{
		if (mixIndex[i].id == fileID)
			return mixIndex[i].offset + startingOffset + bodyOffset;
	}
	std::cout << "File not found (no offset returned): " << fileID << std::endl;
	return mixIndex[0].offset + startingOffset + bodyOffset;
}

int MixFile::getAFileSize(__int32 fileID)
{
	for (unsigned int i = 0; i < mixIndex.size(); ++i)
	{
		if (mixIndex[i].id == fileID)
			return mixIndex[i].size;
	}
	std::cout << "File not found (no size returned): " << fileID << std::endl;
	return mixIndex[0].size;
}

std::vector<byte> MixFile::getFile(__int32 fileID)
{
	std::vector<byte> fileBytes;
	for (unsigned int i = 0; i < mixIndex.size(); ++i)
	{
		if (mixIndex[i].id == fileID)
		{
			fileBytes.resize(mixIndex[i].size);
			fileBytes = mixReader->readByteBlockFromOffset(mixIndex[i].offset + startingOffset + bodyOffset, mixIndex[i].size);
			return fileBytes;
		}
	}
	return fileBytes;
}

void MixFile::determineMixReader()
{
	if (parent == nullptr)
	{
		std::cout << "Using own reader" << std::endl;
		//mixReader = &mixReader;
	}
	else
	{
		std::cout << "Using parent's reader" << std::endl;
		//mixReader = &parent->mixReader;
	}
}

void MixFile::dumpIndex()
{
	std::cout << "Dumping index of " << mixName << std::endl;
	for (unsigned int i = 0; i < mixIndex.size(); ++i)
	{
		std::cout << "ID: " << mixIndex[i].id << " Offset: " << mixIndex[i].offset << " Size: " << mixIndex[i].size << std::endl;
	}
	std::cout << "End of dump" << std::endl;
}