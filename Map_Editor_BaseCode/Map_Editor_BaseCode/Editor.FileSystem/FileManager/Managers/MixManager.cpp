/*
 * MixFileHandler.cpp
 *
 *  Created on: 12 feb. 2014
 *      Author: Rik
 *	  Semester: CAR
 */

#include "stdafx.h"
#include "MixManager.hpp"
#include "../../MixFile/Ccrc.hpp"
#include "../../../Log.hpp"
#include "../../../Config.hpp"
#include <cstring>
#include <algorithm>
#include <iostream>
#include <sstream>

/* static */ MIXManager* MIXManager::manager;
/* static */ MIXManager* MIXManager::getManager()
{
	if (manager)
		return manager;
	else
		manager = new MIXManager();
	return manager;
}

MIXManager::MIXManager()
{

}

void MIXManager::assign(RawFileSystem* _rawSystem)
{
	rawSystem = _rawSystem;
}

void MIXManager::cache(const std::string& _mixName)
{
	std::string mixName = _mixName;
	std::transform(mixName.begin(), mixName.end(), mixName.begin(), ::toupper);
	//std::cout << "Processing: " << mixName << std::endl;
	/*
		Flow:
		Check if file exists in root:
		-> YES: Easy! Let RawManager create a reader and return it
		-> NO: Find the upper parent and have RawManager return it
		*/
	if (rawSystem->fileIsInGameRoot(mixName))
		mixFiles.push_back(std::make_unique<MixFile>(rawSystem->getReaderOfFile(mixName), 0, 0, mixName));
		//mixFiles.push_back(std::make_unique<MixFile>(rawSystem->getReaderOfFile(mixName), 0, 0, mixName));
	else if (rawSystem->fileIsInEditorRoot(mixName))
		mixFiles.push_back(std::make_unique<MixFile>(rawSystem->getReaderOfEditorFile(mixName), 0, 0, mixName));
		//mixFiles.push_back(std::make_unique<MixFile>(rawSystem->getReaderOfEditorFile(mixName), 0, 0, mixName));
	else
	{
		/* This gets the name of hte MIX holding the file */
		std::string containingMix = getName(mixName);

		//Don't try shit when it's not there
		if (containingMix == "")
			return;

		/* This gets the MIX that holds the file/mix */
		MixFile* theMix = get(containingMix);

		/* Trivial stuff, gets the offset and filesize from the MIX index */
		int mixID = convertToID(mixName);
		int offset = theMix->getAFileOffset(mixID);
		int size = theMix->getAFileSize(mixID);

		/* This gets the name of the upper parent (which is located in the root */
		std::string parentName = theMix->getUpperParentName();
		MixFile* parentMix = get(parentName);

		/* Creates the MIX and puts it in the list */
		mixFiles.push_back(std::make_unique<MixFile>(parentMix->mixReader, offset, size, mixName));
		//mixFiles.push_back(std::make_unique<MixFile>(rawSystem->getReaderOfFile(parentName), offset, size));
	}

	Log::note("MIX: " + mixName + " succesfully cached.", Log::DEBUG);
}

		/*


	if (parentMixName != "") //This mix has a parent
	{
		//Get mix from name
		for (unsigned int i = 0; i < mixFiles.size(); ++i)
		{
			//std::cout << "possible parent: " << mixFiles[i]->mixName << " | required parent: " << parentMixName << std::endl;
			if (mixFiles[i]->mixName == parentMixName)
			{
				int mixID = convertNameToID(_mixName);
				//currentMix = new MixFile(_mixName, mixFiles[i], mixID);
				mixFiles.push_back(std::make_unique<MixFile>(_mixName, mixFiles[i], mixID));
			//	std::cout << "Mix created with pointer: " << currentMix << std::endl;
				break;
			}
		}
	}
	else //This mix has no parent
	{
		//currentMix = new MixFile(_mixName);
		//std::cout << "Mix created with pointer: " << currentMix << std::endl;
		mixFiles.push_back(std::make_unique<MixFile>(_mixName));
	}
}*/

int MIXManager::convertToID(std::string name)
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

MixFile* MIXManager::get(const std::string& _mixName)
{
	std::string mixName = _mixName;
	std::transform(mixName.begin(), mixName.end(), mixName.begin(), ::toupper);

	for (const auto &iter : mixFiles)
	{
		if (iter->mixName == mixName)
		{
			return iter.get();
		}
	}
	return nullptr;
}

bool MIXManager::inAMix(const std::string& fileName)
{
	int fileID = convertToID(fileName);

	for (const auto &iter : mixFiles)
	{
		if (iter->checkFileExistance(fileID))
			return true;
	}
	return false;
}

std::string MIXManager::getName(const std::string& fileName)
{
	int fileID = convertToID(fileName);

	for (const auto &iter : mixFiles)
	{
		if (iter->checkFileExistance(fileID))
			return iter->getUpperParentName();
	}
	return "";
}

BinaryReader* MIXManager::getReader(const std::string& fileName)
{
	if (inAMix(fileName) == true)
	{
		MixFile* aMix = get(getName(fileName));
		return aMix->mixReader;
	}
	else
		return nullptr;
}

__int32 MIXManager::getOffsetForFile(const std::string& fileName)
{
	__int32 id = convertToID(fileName);
	for (const auto &iter : mixFiles)
	{
		if (iter->checkFileExistance(id))
			return iter->getAFileOffset(id);
	}

	return -1;
}

int MIXManager::getSizeForFile(const std::string& fileName)
{
	__int32 id = convertToID(fileName);
	for (const auto &iter : mixFiles)
	{
		if (iter->checkFileExistance(id))
			return iter->getAFileSize(id);
	}

	return 0;
}

void MIXManager::extract(const std::string& fileName, const std::string& mixName /* = "" */)
{
	if (rawSystem->fileIsInGameRoot(fileName))
	{
		Log::note("EXTRACTION - File with name '" + fileName + "' already exists in the game's root!", Log::DEBUG);
		return;
	}
	else if (rawSystem->fileIsInEditorRoot(fileName))
	{
		Log::note("EXTRACTION - File with name '" + fileName + "' already exists in the editor's root!", Log::DEBUG);
		return;
	}
	
	std::vector<byte> fileBytes;
	int id = convertToID(fileName);
	std::string parentMixName;
	
	if (mixName.empty())
	{
		parentMixName = getName(fileName);
	}
	else
	{
		parentMixName = mixName;
	}
	
	MixFile* theMix = get(parentMixName);

	if (!theMix)
	{
		Log::note("EXTRACTION - MIX with name '" + parentMixName + "' does not exist, aborting extraction.", Log::DEBUG);
		return;
	}

	fileBytes = theMix->getFile(id);

	std::ofstream dicks(Config::editorRoot + Config::backSlash + fileName, std::ios::out | std::ios::binary);
	if (dicks.is_open() && fileBytes.size() > 0)
	{
		//Log::note("Extracting following file from: " + parentMixName, Log::DEBUG);
		for (unsigned int i = 0; i < fileBytes.size(); ++i)
		{
			dicks << fileBytes[i];
		}
		Log::note("EXTRACTION - File with name '" + fileName + "' has been written to the root of the editor.", Log::DEBUG);
		dicks.close();
	}
	else if (mixName.empty())
	{
		Log::note("Unable to write file '" + fileName + "'.", Log::DEBUG);
	}
	else
	{
		Log::note("Unable to write file '" + fileName + "' from MIX with name '" + mixName + "'.", Log::DEBUG);
	}
}