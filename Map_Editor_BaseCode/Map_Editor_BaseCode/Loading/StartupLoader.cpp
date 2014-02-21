#include "stdafx.h"
#include "StartupLoader.hpp"
#include "../GlobalData.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <windows.h>

StartupLoader::StartupLoader(MixFileHandler* _mixHandler)
:mixHandler(_mixHandler)
{

}

void StartupLoader::initiateMIX()
{
	WIN32_FIND_DATA ffd;
	std::string installMix = GlobalData::installDir + GlobalData::backSlash + "*.mix";
	std::wstring dir(installMix.begin(), installMix.end());
	const wchar_t* dirChar = dir.c_str();

	HANDLE hFind = FindFirstFile(dirChar, &ffd);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		std::cout << "Invalid MIX file!" << std::endl;
	}

	bool finished = false;
	int i = 1;
	while (!finished)
	{
		std::wstring wFileName = ffd.cFileName;
		std::string fileName(wFileName.begin(), wFileName.end());
		std::transform(fileName.begin(), fileName.end(), fileName.begin(), ::toupper);
		std::cout << "Found in DIR: " << fileName << std::endl;
		filenames.push_back(fileName);

		if (!FindNextFile(hFind, &ffd))
			finished = true;
		++i;
	}
	FindClose(hFind);
	
	std::string elocal = "ELOCAL";
	std::string ecache = "ECACHE";
	std::string expand = "EXPAND";
	std::string missionDisk = "MD";

	//findExpandMIX(expand, missionDisk);	
	findRootGameMIX(missionDisk);
	findEcacheMIX(elocal, ecache);

	if (expandFileNames.size() > 0)
		modFileNames.insert(modFileNames.end(), expandFileNames.begin(), expandFileNames.end());
	if (gameFileNames.size() > 0)
		modFileNames.insert(modFileNames.end(), gameFileNames.begin(), gameFileNames.end());
	if (getEcacheFiles()->size() > 0)
		modFileNames.insert(modFileNames.end(), ecacheFileNames.begin(), ecacheFileNames.end());

	if (modFileNames.size() > 0)
	{
		for (unsigned int i = 0; i < modFileNames.size(); ++i)
		{
			std::cout << "--------------------------------------------------" << std::endl;
			mixHandler->createVirtualMix(modFileNames[i]);
		}
		findSubGameMIX(missionDisk);
	}
	else
		std::cout << "No MIX files found!" << std::endl;
}

void StartupLoader::findRootGameMIX(const std::string missionDisk)
{
	for (unsigned int i = 0; i < filenames.size(); ++i)
	{
		//Maybe there should be support added for "expandmd01.mix" as it's used for YR 1.001
		if (   filenames[i] == "RA2.MIX"							|| filenames[i] == "RA2MD.MIX" 
			|| filenames[i] == "MAPS01.MIX"							|| filenames[i] == "MAPS02.MIX"
			|| filenames[i] == "MAPS" + missionDisk + "03.MIX"		|| filenames[i] == "THEME.MIX"
			|| filenames[i] == "MULTI.MIX"							|| filenames[i] == "MULTI" + missionDisk + ".MIX"
			|| filenames[i] == "LANGUAGE.MIX"						|| filenames[i] == "LANGMD.MIX")
		{
			//std::cout << "Found base game MIX: " << filenames[i] << std::endl;
			gameFileNames.push_back(filenames[i]);
		}
	}
}

void StartupLoader::findSubGameMIX(const std::string missionDisk)
{	
	int suffixLoopInt = 0;
	bool withMD = false;
	while (suffixLoopInt < 2)
	{
		std::vector<std::string> coreMixFileNames = getMixNames(withMD);
		for (unsigned int i = 0; i < coreMixFileNames.size(); ++i)
		{
			std::string searchFileName = coreMixFileNames[i];
			// CHECKING IN ROOT
			std::cout << "\n=========================================================================\nNow looking for: " << searchFileName << std::endl;
			if (checkFileInRoot(searchFileName) == true)
			{
				std::cout << "Found in root, creating as parent mix.." << std::endl;
				mixHandler->createVirtualMix(searchFileName);
			}
			else
			{
				std::string parentMixName = mixHandler->getMixNameOfFile(searchFileName);				
				if (parentMixName != "")
				{
					std::cout << "Found in: " << parentMixName << ", creating as child mix..." << std::endl;
					mixHandler->createVirtualMix(searchFileName, parentMixName);
				}
				else
				{
					std::cout << "MIX: " << searchFileName << " not found anywhere." << std::endl;
				}
			}
		}
		suffixLoopInt++;
		withMD = true;
	}
	std::cout << "\nDone looping, all mix files processed.\n***************************************************\n\n" << std::endl;
}

void StartupLoader::findExpandMIX(const std::string& expand, const std::string& missionDisk)
{
	for (unsigned int i = 0; i < 100; ++i)
	{
		std::stringstream numberStream;
		if (i < 10)
			numberStream << 0 << i;
		else
			numberStream << i;
	
		for (unsigned int j = 0; j < filenames.size(); ++j)
		{
			if (filenames[j] == expand + missionDisk + numberStream.str() + ".MIX")
			{
				//std::cout << "Found 'expandmd' MIX file: " << filenames[j] << std::endl;
				expandFileNames.insert(expandFileNames.begin(), filenames[j]);
			}
		}
	}
}

void StartupLoader::findEcacheMIX(const std::string& elocal, const std::string& ecache)
{
	for (unsigned int i = 0; i < filenames.size(); ++i)
	{
		if (filenames[i].substr(0, elocal.size()) == elocal)
		{
			//std::cout << "Found 'elocal' MIX file: " << filenames[i] << std::endl;
			ecacheFileNames.push_back(filenames[i]);
		}
		else if (filenames[i].substr(0, ecache.size()) == ecache)
		{
			//std::cout << "Found 'ecache' MIX file: " << filenames[i] << std::endl;
			ecacheFileNames.push_back(filenames[i]);
		}
	}
}

std::vector<std::string>* StartupLoader::getGameFiles() 
{
	return &gameFileNames; 
}

std::vector<std::string>* StartupLoader::getExpandFiles()
{
	return &expandFileNames;
}

std::vector<std::string>* StartupLoader::getEcacheFiles()
{
	return &ecacheFileNames;
}

bool StartupLoader::checkFileInRoot(const std::string& fileName)
{
	for (unsigned int i = 0; i < filenames.size(); ++i)
	{
		if (filenames[i] == fileName)
			return true;
	}
	return false;
}

/*
	IMPORTANT:
	- Should core mixes also have the modified mission disk name?
	- Currently sticking with 'MD' suffix
*/
std::vector<std::string> StartupLoader::getMixNames(bool missionDisk /* = false */)
{
	std::vector<std::string> coreMixNames;
	if (missionDisk)
	{
		coreMixNames.push_back("CACHEMD.MIX");
		coreMixNames.push_back("CONQMD.MIX");
		coreMixNames.push_back("DES.MIX");
		coreMixNames.push_back("DESERT.MIX");
		coreMixNames.push_back("GENERMD.MIX");
		coreMixNames.push_back("ISODES.MIX");
		coreMixNames.push_back("ISODESMD.MIX");
		coreMixNames.push_back("ISOGENMD.MIX");
		coreMixNames.push_back("ISOLUN.MIX");
		coreMixNames.push_back("ISOLUNMD.MIX");
		coreMixNames.push_back("ISOSNOMD.MIX");
		coreMixNames.push_back("ISOTEMMD.MIX");
		coreMixNames.push_back("ISOUBN.MIX");
		coreMixNames.push_back("ISOUBNMD.MIX");
		coreMixNames.push_back("ISOURBMD.MIX");
		coreMixNames.push_back("LOCALMD.MIX");
		coreMixNames.push_back("LUN.MIX");
		coreMixNames.push_back("LUNAR.MIX");
		coreMixNames.push_back("SNOWMD.MIX");
		coreMixNames.push_back("UBN.MIX");
		coreMixNames.push_back("URBANN.MIX");
		coreMixNames.push_back("AUDIOMD.MIX");
	}
	else
	{
		coreMixNames.push_back("CACHE.MIX");
		coreMixNames.push_back("CONQUER.MIX");
		coreMixNames.push_back("GENERIC.MIX");
		coreMixNames.push_back("ISOGEN.MIX");
		coreMixNames.push_back("ISOSNOW.MIX");
		coreMixNames.push_back("ISOTEMP.MIX");
		coreMixNames.push_back("ISOURB.MIX");
		coreMixNames.push_back("LOCAL.MIX");
		coreMixNames.push_back("SNO.MIX");
		coreMixNames.push_back("SNOW.MIX");
		coreMixNames.push_back("TEM.MIX");
		coreMixNames.push_back("TEMPERAT.MIX");
		coreMixNames.push_back("URB.MIX");
		coreMixNames.push_back("URBAN.MIX");
		coreMixNames.push_back("AUDIO.MIX");
	}

	return coreMixNames;
}