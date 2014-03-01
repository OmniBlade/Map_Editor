/*
 * MixFileHandler.cpp
 *
 *  Created on: 12 feb. 2014
 *      Author: Rik
 *	  Semester: CAR
 */

#include "stdafx.h"
#include "MixFileHandler.hpp"
#include "../Reading/BinaryReader.hpp"
#include "../FileSystem/MixFile/KeyCalculator.hpp"
#include "../FileSystem/MixFile/Blowfish.hpp"
#include "../FileSystem/MixFile/Ccrc.hpp"
#include <cstring>
#include <algorithm>
#include <iostream>
#include <sstream>

MixFileHandler::MixFileHandler()
:currentMix(nullptr)
{

}

void MixFileHandler::createVirtualMix(const std::string& _mixName, const std::string& parentMixName)
{
	std::cout << "Processing: " << _mixName << std::endl;
	if (parentMixName != "") //This mix has a parent
	{
		//Get mix from name
		for (unsigned int i = 0; i < mixFiles.size(); ++i)
		{
			//std::cout << "possible parent: " << mixFiles[i]->mixName << " | required parent: " << parentMixName << std::endl;
			if (mixFiles[i]->mixName == parentMixName)
			{
				int mixID = convertNameToID(_mixName);
				currentMix = new MixFile(_mixName, mixFiles[i], mixID);
				mixFiles.push_back(currentMix);
				std::cout << "Mix created with pointer: " << currentMix << std::endl;
				break;
			}
		}
	}
	else //This mix has no parent
	{
		currentMix = new MixFile(_mixName);
		std::cout << "Mix created with pointer: " << currentMix << std::endl;
		mixFiles.push_back(currentMix);
	}
}

std::vector<MixFile*>* MixFileHandler::getMixFiles()
{
	return &mixFiles;
}

int MixFileHandler::convertNameToID(std::string name)
{
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	const int l = name.length();
	int a = l >> 2;
	if (l & 3)
	{
		name += static_cast<char>(l - (a << 2));
		int i = 3 - (l & 3);
		while (i--)
			name += name[a << 2];
	}
	Ccrc crc;                        // use a normal CRC function
	crc.init();
	crc.do_block(name.c_str(), name.length());
	return crc.get_crc();
}

MixFile* MixFileHandler::getMixByName(const std::string& _mixName)
{
	for (unsigned int i = 0; i < mixFiles.size(); ++i)
	{
		if (mixFiles[i]->mixName == _mixName)
			return mixFiles[i];
	}
	return nullptr;
}

bool MixFileHandler::checkFileInMixes(const std::string& fileName)
{
	int fileID = convertNameToID(fileName);
	for (unsigned int i = 0; i < mixFiles.size(); ++i)
	{
		if (mixFiles[i]->checkFileExistance(fileID))
			return true;
	}
	return false;
}

std::string MixFileHandler::getMixNameOfFile(const std::string& fileName)
{
	int fileID = convertNameToID(fileName);
	for (unsigned int i = 0; i < mixFiles.size(); ++i)
	{
		if (mixFiles[i]->checkFileExistance(fileID))
			return mixFiles[i]->mixName;
	}
	return "";
}

void MixFileHandler::extractFileFromMix(const std::string& fileName)
{
	std::cout << "******************//////////////////****************" << std::endl;
	std::vector<byte> fileBytes;
	int id = convertNameToID(fileName);
	std::cout << "gotten id: " << id << std::endl;
	std::string parentMixName = getMixNameOfFile(fileName);
	std::cout << "gotten file it is in: " << parentMixName << std::endl;
	MixFile* theMix = getMixByName(parentMixName);
	std::cout << "Gotten mix pointer: " << theMix << std::endl;

	std::cout << "File exists: " << std::endl;
	std::cout << theMix->checkFileExistance(id) << std::endl;

	fileBytes = theMix->getFileByID(id);
	std::cout << "filled vector " << std::endl;

	theMix->dumpIndex();
	std::cout << "File byte size: " << fileBytes.size() << " extracting from: " << parentMixName <<std::endl;

	std::ofstream dicks(fileName, std::ios::out | std::ios::binary);
	if (dicks.is_open())
	{
		for (unsigned int i = 0; i < fileBytes.size(); ++i)
		{
			dicks << fileBytes[i];
			//std::cout << fileBytes[i] << "|";
		}
		std::cout << "File: " << fileName << " written!" << std::endl;
		dicks.close();
	}
	else
	{
		std::cout << "Too retarded to write..." << std::endl;
	}
}

BinaryReader* MixFileHandler::getReaderFromMIX(const std::string& fileName)
{
	if (checkFileInMixes(fileName) == true)
	{
		MixFile* aMix = getMixByName(getMixNameOfFile(fileName));
		return aMix->aMixReader;
	}
	else
		return nullptr;
}

void MixFileHandler::dumpMIXNames()
{
	std::cout << "Currently in memory: " << std::endl;
	for (unsigned int i = 0; i < mixFiles.size(); ++i)
	{
		std::cout << "Mix Name: " << mixFiles[i]->mixName << " pointer: " << mixFiles[i] << std::endl;
	}
}