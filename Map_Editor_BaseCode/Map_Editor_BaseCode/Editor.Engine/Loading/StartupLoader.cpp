#include "stdafx.h"
#include "StartupLoader.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/MixManager.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Config.hpp"
#include "../../Log.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <windows.h>

StartupLoader::StartupLoader()
{

}

void StartupLoader::initiateMIX()
{
	WIN32_FIND_DATA ffd;
	std::string installIni = Config::installDir + Config::backSlash + "*.mix";
	std::wstring dir(installIni.begin(), installIni.end());
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
		mixFilenames.push_back(fileName);

		if (!FindNextFile(hFind, &ffd))
			finished = true;
		++i;
	}
	FindClose(hFind);
	
	std::vector<std::string>& mixList = getExpandMixes();
	std::vector<std::string>& mainMixes = getMainMixes();
	std::vector<std::string>& subMixes = getSubMixes();
	std::vector<std::string>& ecacheMixes = getEcacheMixes();

	mixList.insert(mixList.end(), mainMixes.begin(), mainMixes.end());
	mixList.insert(mixList.end(), ecacheMixes.begin(), ecacheMixes.end());
	mixList.insert(mixList.end(), subMixes.begin(), subMixes.end());

	for (unsigned int i = 0; i < mixList.size(); ++i)
	{
		//std::cout << "Trying to cache: " << mixList[i] << "." << std::endl;
		MIXManager::getManager()->cache(mixList[i]);
	}
}

void StartupLoader::findRootGameMIX(std::vector<std::string>& filesVector)
{
	for (unsigned int i = 0; i < mixFilenames.size(); ++i)
	{
		//TODO Maybe there should be support added for "expandmd01.mix" as it's used for YR 1.001
		//TODO Either scratch MissionDisk from MAPSMD03, or give them all entries in the config file
		//TODO Decide whether vanilla mission maps should be opened through the editor (like in SC 2)
		/*
			Files and their usage:
			- RA2.MIX		-> Holds all important files for RA2
			- RA2MD.MIX		-> Holds all important files for YR
			- MAPS01.MIX	-> Holds the Allied missions for RA2
			- MAPS02.MIX	-> Holds the Soviet missions for RA2
			- MAPSMD03.MIX	-> Holds all missions for YR
			- MULTI.MIX		-> Holds all RA2's multiplayer maps
			- MULTIMD.MIX	-> Holds all YR's multiplayer maps
			- THEME.MIX		-> Holds RA2's music themes (part of testcode)
			- LANGUAGE.MIX	-> Holds RA2's stringtable
			- LANGMD.MIX	-> Holds YR's stringtable
		*/
		if	  (mixFilenames[i] == "RA2.MIX"			|| mixFilenames[i] == "RA2MD.MIX"
			|| mixFilenames[i] == "MAPS01.MIX"		|| mixFilenames[i] == "MAPS02.MIX"
			|| mixFilenames[i] == "MAPS" + Config::missionDisk + "03.MIX"
			|| mixFilenames[i] == "THEME.MIX" || mixFilenames[i] == "THEME" + Config::missionDisk + ".MIX"
			|| mixFilenames[i] == "MULTI.MIX" || mixFilenames[i] == "MULTI" + Config::missionDisk + ".MIX"
			|| mixFilenames[i] == "LANGUAGE.MIX" || mixFilenames[i] == "LANG" + Config::missionDisk + ".MIX")
		{
			filesVector.push_back(mixFilenames[i]);
		}
	}
}


void StartupLoader::initiateINI()
{
	WIN32_FIND_DATA ffd;
	std::string installIni = Config::installDir + Config::backSlash + "*.MIX";
	std::wstring dir(installIni.begin(), installIni.end());
	const wchar_t* dirChar = dir.c_str();

	HANDLE hFind = FindFirstFile(dirChar, &ffd);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		std::cout << "Invalid INI file!" << std::endl;
	}

	bool finished = false;
	int i = 1;
	while (!finished)
	{
		std::wstring wFileName = ffd.cFileName;
		std::string fileName(wFileName.begin(), wFileName.end());
		std::transform(fileName.begin(), fileName.end(), fileName.begin(), ::toupper);
		iniFilenames.push_back(fileName);

		if (!FindNextFile(hFind, &ffd))
			finished = true;
		++i;
	}
	FindClose(hFind);

	std::vector<std::string> iniFiles = getIniNames();

	for (unsigned int i = 0; i < iniFiles.size(); ++i)
	{
		//std::cout << "Trying to cache: " << iniFiles[i] << std::endl;
		INIManager::getManager()->cache(iniFiles[i]);
	}

	//findINIFiles();
}

void StartupLoader::findINIFiles()
{
	std::vector<std::string> coreIniFiles = getIniNames();
	for (unsigned int i = 0; i < coreIniFiles.size(); ++i)
	{
		std::cout << "\n======= " << coreIniFiles[i] << " =======" << std::endl;
		__int32 fileOffset = 0;
		int fileSize = 0;
		bool inRoot = false;
		//Found in ROOT
		if (checkIniInRoot(coreIniFiles[i]))
		{
			INIManager::getManager()->cache(coreIniFiles[i]);
			inRoot = true;
			Log::note("INI '" + coreIniFiles[i] + "' found in root", Log::DEBUG);
		}
		else
		{
			MixFile* theMix;
			std::string parentMixName;
			if (MIXManager::getManager()->inAMix(coreIniFiles[i]))
			{
				parentMixName = MIXManager::getManager()->getName(coreIniFiles[i]);
				Log::note("INI '" + coreIniFiles[i] + "' found inside MIX '" + parentMixName + "'", Log::DEBUG);
				theMix = MIXManager::getManager()->get(parentMixName);
				parentMixName = theMix->getUpperParentName();
				fileOffset = theMix->getAFileOffset(MIXManager::getManager()->convertToID(coreIniFiles[i]));
				fileSize = theMix->getAFileSize(MIXManager::getManager()->convertToID(coreIniFiles[i]));

				INIManager::getManager()->cache(coreIniFiles[i]);
			}
			else
			{
				Log::note("Unable to find: " + coreIniFiles[i] + " in any MIX!", Log::DEBUG);
			}
		}
		/*//Found in a MIX file
		else if (mixHandler->checkFileInMixes(coreIniFiles[i]) && inRoot == false)
		{
			std::string parentMixName = mixHandler->getMixNameOfFile(coreIniFiles[i]);
			MixFile* theMix = mixHandler->getMixByName(parentMixName);
			fileOffset = theMix->getAFileOffset(mixHandler->convertNameToID(coreIniFiles[i]));
			fileSize = theMix->getAFileSize(mixHandler->convertNameToID(coreIniFiles[i]));

		/*	//Check the MIX for a parent
			if (theMix->parent != nullptr)
			{
				//parentMixName = theMix->parent->mixName;
				fileOffset = theMix->getAFileOffset(mixHandler->convertNameToID(coreIniFiles[i]));
				fileSize = theMix->getAFileSize(mixHandler->convertNameToID(coreIniFiles[i]));
			}
			else
			{
				fileOffset = theMix->getAFileOffset(mixHandler->convertNameToID(coreIniFiles[i]));
				fileSize = theMix->getAFileSize(mixHandler->convertNameToID(coreIniFiles[i]));
			}*/
			
			
			
			
			/*while (true)
			{
				//See if the parent's parent is filled (oh god...)
				if (theMix->parent != nullptr)
				{
					std::cout << "Mix: " << theMix->mixName << " has a parent: " << theMix->parent->mixName << std::endl;
					theMix = theMix->parent;
				}
				else
				{
					std::cout << "Getting fileoffset and size from MIX: " << theMix->mixName << std::endl;
					parentMixName = theMix->mixName;
					fileOffset = theMix->getAFileOffset(mixHandler->convertNameToID(coreIniFiles[i]));
					fileSize = theMix->getAFileSize(mixHandler->convertNameToID(coreIniFiles[i]));
					break;
				}
			}*/

			/*if (theMix->parent != nullptr)
			{
				parentMixName = theMix->parent->mixName;
				fileOffset = theMix->getAFileOffset(mixHandler->convertNameToID(coreIniFiles[i]));
				fileSize = theMix->getAFileSize(mixHandler->convertNameToID(coreIniFiles[i]));
			}
			else
			{
				fileOffset = theMix->getAFileOffset(mixHandler->convertNameToID(coreIniFiles[i]));
				fileSize = theMix->getAFileSize(mixHandler->convertNameToID(coreIniFiles[i]));
			}
			std::cout << "INI ("<< coreIniFiles[i] << ") found in: " << theMix->mixName << std::endl;
		}
		else
			std::cout << "Unable to locate INI file: " << coreIniFiles[i] << std::endl;*/
	}
}

bool StartupLoader::checkMixFileInRoot(const std::string& fileName)
{
	for (unsigned int i = 0; i < mixFilenames.size(); ++i)
	{
		if (mixFilenames[i] == fileName)
			return true;
	}
	return false;
}

bool StartupLoader::checkIniInRoot(const std::string& fileName)
{
	for (unsigned int i = 0; i < iniFilenames.size(); ++i)
	{
		if (iniFilenames[i] == fileName)
			return true;
	}
	return false;
}

std::vector<std::string> StartupLoader::getMainMixes()
{
	std::vector<std::string> mainMixNames;
	mainMixNames.push_back("LANGMD.MIX");
	mainMixNames.push_back("LANGUAGE.MIX");
	mainMixNames.push_back("RA2MD.MIX");
	mainMixNames.push_back("RA2.MIX");
	mainMixNames.push_back("CACHEMD.MIX");
	mainMixNames.push_back("CACHE.MIX");
	mainMixNames.push_back("LOCALMD.MIX");
	mainMixNames.push_back("LOCAL.MIX");


	/*if (mixFilenames[i] == "RA2.MIX" || mixFilenames[i] == "RA2MD.MIX"
		|| mixFilenames[i] == "MAPS01.MIX" || mixFilenames[i] == "MAPS02.MIX"
		|| mixFilenames[i] == "MAPS" + Config::MAIN_MissionDisk + "03.MIX"
		|| mixFilenames[i] == "THEME.MIX" || mixFilenames[i] == "THEME" + Config::MAIN_MissionDisk + ".MIX"
		|| mixFilenames[i] == "MULTI.MIX" || mixFilenames[i] == "MULTI" + Config::MAIN_MissionDisk + ".MIX"
		|| mixFilenames[i] == "LANGUAGE.MIX" || mixFilenames[i] == "LANG" + Config::MAIN_MissionDisk + ".MIX")
		true;*/

	return mainMixNames;
}

/*
	TODO IMPORTANT:
	- Should core mixes also have the modified mission disk name?
	- Currently sticking with 'MD' suffix
*/
std::vector<std::string> StartupLoader::getSubMixes(bool missionDisk /* = false */)
{
	std::vector<std::string> coreMixNames;

	coreMixNames.push_back("CONQMD.MIX");
	coreMixNames.push_back("GENERMD.MIX");
	coreMixNames.push_back("GENERIC.MIX");
	coreMixNames.push_back("ISOGENMD.MIX");
	coreMixNames.push_back("ISOGEN.MIX");
	coreMixNames.push_back("CONQUER.MIX");
	//Theater shit
	coreMixNames.push_back("TEMPERATMD.MIX");
	coreMixNames.push_back("TEM.MIX");
	coreMixNames.push_back("ISOTEMMD.MIX");
	coreMixNames.push_back("ISOTEMP.MIX");

	coreMixNames.push_back("SNOWMD.MIX");
	coreMixNames.push_back("SNO.MIX");
	coreMixNames.push_back("ISOSNOMD.MIX");
	coreMixNames.push_back("ISOSNOW.MIX");

	coreMixNames.push_back("URBANMD.MIX");
	coreMixNames.push_back("URB.MIX");
	coreMixNames.push_back("ISOURBMD.MIX");
	coreMixNames.push_back("ISOURB.MIX");

	coreMixNames.push_back("DESERTMD.MIX");
	coreMixNames.push_back("DES.MIX");
	coreMixNames.push_back("ISODESMD.MIX");
	coreMixNames.push_back("ISODES.MIX");

	coreMixNames.push_back("URBANNMD.MIX");
	coreMixNames.push_back("UBN.MIX");
	coreMixNames.push_back("ISOUBN.MIX");
	coreMixNames.push_back("ISOUBNMD.MIX");

	coreMixNames.push_back("LUNDARMD.MIX");
	coreMixNames.push_back("LUN.MIX");
	coreMixNames.push_back("ISOLUNMD.MIX");
	coreMixNames.push_back("ISOLUN.MIX");

	/*coreMixNames.push_back("GENERIC.MIX");
	coreMixNames.push_back("ISOGEN.MIX");
	
	coreMixNames.push_back("ISOTEMP.MIX");
	coreMixNames.push_back("ISOURB.MIX");
	coreMixNames.push_back("LOCAL.MIX");
	coreMixNames.push_back("SNO.MIX");
	coreMixNames.push_back("SNOW.MIX");
	coreMixNames.push_back("TEM.MIX");
	coreMixNames.push_back("TEMPERAT.MIX");
	coreMixNames.push_back("URB.MIX");
	coreMixNames.push_back("URBAN.MIX");
	//coreMixNames.push_back("AUDIO.MIX");
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
	//coreMixNames.push_back("AUDIOMD.MIX");*/

	return coreMixNames;
}

/*
	Please note: Order is not important here, as it just caches the INI files and later uses them to parse everything
	TODO: Here again, should mission disk from global data be supported for everything?
*/
std::vector<std::string> StartupLoader::getIniNames()
{
	std::vector<std::string> coreIniNames;
	
	//CORE -- MAIN INIs
	coreIniNames.push_back(Config::rules);
	coreIniNames.push_back(Config::art);
	coreIniNames.push_back(Config::sound);
	coreIniNames.push_back(Config::eva);
	coreIniNames.push_back(Config::theme);
	coreIniNames.push_back(Config::AI);
	//SP/MP specific INIs
	coreIniNames.push_back(Config::battle);
	coreIniNames.push_back(Config::coop);
	coreIniNames.push_back(Config::modes);
	//coreIniNames.push_back("MAPSEL" +	Config::MIX_missionDisk + ".INI"); // This is no TS!
	//CORE -- THEATERS
	//Loaded only on demand (eg. creating / loading a map)
	//coreIniNames.push_back("SNOW" +		Config::MIX_missionDisk + ".INI");
	//coreIniNames.push_back("TEMPERAT" + Config::MIX_missionDisk + ".INI");
	//coreIniNames.push_back("URBAN" +	Config::MIX_missionDisk + ".INI");
	//coreIniNames.push_back("DESERT" +	Config::MIX_missionDisk + ".INI");
	//coreIniNames.push_back("LUNAR" +	Config::MIX_missionDisk + ".INI");
	//coreIniNames.push_back("URBANN" +	Config::MIX_missionDisk + ".INI");

	return coreIniNames;
}

std::vector<std::string> StartupLoader::getExpandMixes()
{
	std::vector<std::string> expandMixNames;
	std::stringstream number;

	for (unsigned int i = 99; i > 0; --i)
	{
		if (i < 10)
			number << '0';
		number << i;
		expandMixNames.push_back(Config::expand + Config::missionDisk + number.str() + ".MIX");
		number.str(std::string());
	}
	return expandMixNames;

	for (unsigned int i = 0; i < 99; ++i)
	{
		std::stringstream numberStream;
		if (i < 10)
			numberStream << 0 << i;
		else
			numberStream << i;

		for (unsigned int j = 0; j < mixFilenames.size(); ++j)
		{
			if (mixFilenames[j] == Config::expand + Config::missionDisk + numberStream.str() + ".MIX")
			{
				//std::cout << "Found 'expandmd' MIX file: " << filenames[j] << std::endl;
				expandMixNames.insert(expandMixNames.begin(), mixFilenames[j]);
			}
		}
	}

	return expandMixNames;
	/*
	std::stringstream number;
	
	for (unsigned int i = 99; i > 0; --i)
	{
		if (i < 10)
			number << "0";
		number << i;
		expandMixNames.push_back(Config::MAIN_Expand + number.str() + Config::MAIN_MissionDisk + ".MIX");
		number.str(std::string());
	}
	return expandMixNames;*/
}

std::vector<std::string> StartupLoader::getEcacheMixes()
{
	std::vector<std::string> ecacheMixNames;

	// NOTE: Following code to load ecacheXX.mix files only applies to Tiberian Sun!

	/*std::stringstream number;

	//Ecache 99-00 loop..
	for (unsigned int i = 99; i > 0; --i)
	{
		if (i < 10)
			number << '0';
		number << i;

		ecacheMixNames.push_back(Config::ecache + Config::missionDisk + number.str() + ".MIX");
		number.str(std::string());
	}*/

	//Any ecache* loop...
	for (unsigned int i = 0; i < mixFilenames.size(); ++i)
	{
		if (mixFilenames[i].substr(0, Config::ecache.size()) == Config::elocal)
		{
			// Don't want to put stuff in that's already there...
			if (std::find(ecacheMixNames.begin(), ecacheMixNames.end(), mixFilenames[i]) != ecacheMixNames.end())
				ecacheMixNames.push_back(toProcessMixFileNames[i]);
		}
	}

	// NOTE: The following code to load elocalXX.mix files only applies to Tiberian Sun!

	//Elocal 99-00 loop...
	/*for (unsigned int i = 99; i > 0; --i)
	{
		if (i < 10)
			number << '0';
		number << i;

		ecacheMixNames.push_back(Config::elocal + Config::missionDisk + number.str() + ".MIX");
		number.str(std::string());
	}*/

	for (unsigned int i = 0; i < mixFilenames.size(); ++i)
	{
		if (mixFilenames[i].substr(0, Config::ecache.size()) == Config::ecache)
		{
			// Don't want to put stuff in that's already there...
			if (std::find(ecacheMixNames.begin(), ecacheMixNames.end(), mixFilenames[i]) != ecacheMixNames.end())
				ecacheMixNames.push_back(toProcessMixFileNames[i]);
		}
	}

	return ecacheMixNames;
	
	/*std::stringstream number;
	
	for (unsigned int i = 99; i > 0; --i)
	{
		if (i < 10)
			number << "0";
		number << i;
		ecacheMixNames.push_back(Config::MAIN_Ecache + Config::MAIN_MissionDisk + number.str() + ".MIX");
		number.str(std::string());
	}

	for (unsigned int i = 99; i > 0; --i)
	{
		if (i < 10)
			number << "0";
		number << i;
		ecacheMixNames.push_back(Config::MAIN_Elocal + Config::MAIN_MissionDisk + number.str() + ".MIX");
		number.str(std::string());
	}

	return ecacheMixNames;*/
}