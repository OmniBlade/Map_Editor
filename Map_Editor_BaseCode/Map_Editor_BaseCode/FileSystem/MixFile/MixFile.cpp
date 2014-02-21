/*
 * MixFile.cpp
 *
 *  Created on: 12 feb. 2014
 *      Author: Rik
 *	  Semester: CAR
 */

#include "stdafx.h"
#include "MixFile.hpp"
#include "KeyCalculator.hpp"
#include "Blowfish.hpp"
#include "Ccrc.hpp"
#include "../../GlobalData.hpp"
#include <cstring>
#include <algorithm>
#include <iostream>

//PARENT
MixFile::MixFile(const std::string& _name, MixFile* _parent, int fileID)
: mixName(_name), mixReader(GlobalData::installDir + GlobalData::backSlash + _name), parent(_parent)
{
	std::cout << "MixFile values, Name: " << _name << " Parent: " << _parent << " fileID: " << fileID << std::endl;
	if (_parent != nullptr)//TEMP, only if the offset of a child has to be set to the starting position of the child mix
	{
		//startingOffset = _parent->getAFileOffset(fileID);
		//std::cout << "Starting offset from child is: " << startingOffset << std::endl;
	}
	determineMixReader();
	handleHeader();
}

void MixFile::handleHeader()
{
	//aMixReader->setOffset(startingOffset);
	std::cout << "Current offset: " << aMixReader->getOffset() << std::endl;
	unsigned short possibleCount = aMixReader->readUShort();

	if (possibleCount != 0)
	{
		std::cout << "V1" << std::endl;
		readTDHeader(possibleCount);
		//Set offset to the start of body
		startingOffset += 12 * mixIndex.size() + aMixReader->getOffset();
	}
	else if (possibleCount == 0)
	{
		std::cout << "V2";
		unsigned short flags = aMixReader->readUShort();
		if ((flags & 2) == 0) //Durr
		{
			std::cout << " Unencrypted" << std::endl;
			//Need to read out the files because TD header takes filecount as a parameter
			unsigned short fileCount = aMixReader->readUShort();
			readTDHeader(fileCount);
			//Set offset to the start of body
			startingOffset += 12 * mixIndex.size() + aMixReader->getOffset();
		}
		else if ((flags & 2) != 0) //2 is the identifier for Encryption
		{
			std::cout << " Encrypted" << std::endl;
			readRAHeader();
			startingOffset += ((((12 * mixIndex.size()) + 7) / 8) * 8) + aMixReader->getOffset();
		}
	}
	else
	{
		std::cout << "Unable to determine MIX Version!" << std::endl;
	}

	std::cout << "Offset after header reading: " << startingOffset << std::endl;

	/*
	std::cout << "HAndle header " << startingOffset << std::endl;
	bool isRAMix = false, isEncrypted = false, hasChecksum = false;
		aMixReader->setOffset(startingOffset);
	
	std::cout << "Startingoffset set to: " << startingOffset << std::endl;
	unsigned int mixDetermination = aMixReader->readUInt();
	std::cout << "Determination value: " << mixDetermination << std::endl;
	//aMixReader->restoreOffset();

	std::cout << "offset set2 " << startingOffset << std::endl;

	isRAMix = 0 == (mixDetermination & ~(unsigned int)(flags::Checksum | flags::Encrypted));
	std::cout << "Is RA Mix: " << isRAMix << std::endl;

	if (isRAMix == false)
	{
		std::cout << "V1" << std::endl; //Version 1 MIX
		readTDHeader();
		startingOffset += 6;
	}
	else if (isRAMix == true)
	{
		hasChecksum = mixDetermination & flags::Checksum;
		isEncrypted = mixDetermination & flags::Encrypted;
		//std::cout << "Has checksum: " << hasChecksum << " has encryption: " << isEncrypted << std::endl;
		std::cout << "V2"; //Version 2 MIX or V1 without files
		//unsigned short flags = aMixReader->readUShort();
		//aMixReader->setOffset(startingOffset);
		if (isEncrypted) //ENCRYPTED
		{
			std::cout << "Encrypted IF, offset: " << aMixReader->getOffset() << std::endl;
			startingOffset += 96;
			std::cout << "Encrypted if, after startingoffset +=96, offset: " << aMixReader->getOffset() << std::endl;
			std::cout << " Encrypted" << std::endl;
			readRAHeader();
		}
		else
		{
			std::cout << " Unencrypted" << std::endl;
			readTDHeader();
			startingOffset += 10;
		}
	}
	startingOffset += mixIndex.size()*sizeof(t_mix_index_header);
	std::cout << "FINAL OFFSET: " << startingOffset << std::endl;
	*/
}

void MixFile::readTDHeader(unsigned short fileCount)
{
	header.files = fileCount;
	header.size = aMixReader->readUInt();

	std::vector<t_mix_index_header> files(header.files);
	auto item_buffer = aMixReader->readByteBlock(header.files * sizeof(t_mix_index_header));
	for (int i = 0; i < header.files; ++i)
	{
		files[i] = reinterpret_cast<t_mix_index_header*>(&item_buffer[0])[i];
	}
	mixIndex = files;

	std::cout << "Files: " << header.files << std::endl;
}

void MixFile::readRAHeader()
{
	//std::cout << "Filling encryptionBytes vector " << std::endl;
	std::vector<byte> encryptionBytes = aMixReader->readByteBlock(80);
	//std::cout << "File: " << mixName << std::endl;
	//std::cout << "Dumping 80 byte list: " << std::endl;
	//for (unsigned int i = 0; i < encryptionBytes.size(); ++i)
	//{
//		std::cout << "Byte #" << i + 1 << " " << (int) encryptionBytes[i] << std::endl;
//	}

	byte key[56];
	get_blowfish_key(encryptionBytes.data(), key);
	Blowfish blowfish;

	//std::cout << "Dumping 56 byte list: " << std::endl;
	//for (unsigned int i = 0; i < sizeof(key); ++i)
	//{
//		std::cout << "Byte #" << i + 1 << " " << (int)key[i] << std::endl;
//	}

	blowfish.set_key(key, 56);
	//std::cout << "Filling toByte vector " << std::endl;
	std::vector<byte> toByte = aMixReader->readByteBlock(8);
	byte* pE = &toByte[0];
	blowfish.decipher(pE, pE, 8);

	//	std::cout << "First [56] byte: " << (int)key[0] << ", " << (int)key[1] << ", " << (int)key[2] << "," << (int)key[3] << std::endl;

	memcpy(&header, pE, sizeof(t_mix_header));

	int c_files = header.files;
	const int cb_index = c_files * sizeof(t_mix_index_header);
	const int cb_f = (cb_index + 5) & ~7;

	//std::cout << "cb_f " << cb_f << std::endl;
	//std::cout << "Filling 'auto' file_buffer " << std::endl;
	auto file_buffer = aMixReader->readByteBlock(cb_f);
	blowfish.decipher(file_buffer.data(), &file_buffer[0], cb_f);
	std::vector<t_mix_index_header> files(header.files);
	memcpy(reinterpret_cast<byte*>(&files[0]), &pE[6], 2);
	memcpy(reinterpret_cast<byte*>(&files[0]) + 2, &file_buffer[0], (cb_index - 2));

	mixIndex = files;
	std::cout << "Files: " << files.size() << std::endl;
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
			return mixIndex[i].offset;
	}
	return mixIndex[0].offset;
}

std::vector<byte> MixFile::getFileByID(__int32 fileID)
{
	std::vector<byte> fileBytes;
	std::cout << "Index size: " << mixIndex.size() << std::endl;
	for (unsigned int i = 0; i < mixIndex.size(); ++i)
	{
		if (mixIndex[i].id == fileID)
		{
			fileBytes = aMixReader->readByteBlockFromOffset(mixName, mixIndex[i].offset + startingOffset, mixIndex[i].size);
			//fileBytes = mixReader->readByteBlockFromOffset(mixName, mixIndex[i].size, mixIndex[i].offset);

			std::cout << "Theoretical ID: " << mixIndex[i].id << ", real ID: " << fileID << std::endl;
			std::cout << "Theoretical offset: " << mixIndex[i].offset + startingOffset << std::endl;
			std::cout << "Theoretical size in bytes: " << mixIndex[i].size << std::endl;

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
		aMixReader = &mixReader;
	}
	else
	{
		std::cout << "Using parent's reader" << std::endl;
		aMixReader = &parent->mixReader;
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