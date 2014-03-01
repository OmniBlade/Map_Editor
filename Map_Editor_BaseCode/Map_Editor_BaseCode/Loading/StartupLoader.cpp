#include "stdafx.h"
#include "StartupLoader.hpp"
#include "../GlobalData.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <windows.h>

StartupLoader::StartupLoader(MixFileHandler* _mixHandler, INIFileHandler* _iniHandler)
:mixHandler(_mixHandler), iniHandler(_iniHandler)
{

}

void StartupLoader::initiateMIX()
{
	WIN32_FIND_DATA ffd;
	std::string installMix = GlobalData::MAIN_InstallDir + GlobalData::MAIN_BackSlash + "*.mix";
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
		mixFilenames.push_back(fileName);

		if (!FindNextFile(hFind, &ffd))
			finished = true;
		++i;
	}
	FindClose(hFind);
	
	/*
		Loading order is very important, it has to be just like in the game, see link for more information:
		http://modenc.renegadeprojects.com/MIX
		This explains why the system looks odd
		TODO: LANGUAGE.MIX and LANGMD.MIX are to be loaded before EXPANDMDxx.MIX
	*/

	std::vector<std::string> _expandFileNames;
	std::vector<std::string> _gameFileNames;
	std::vector<std::string> _ecacheFileNames;

	findExpandMIX(_expandFileNames);	
	findRootGameMIX(_gameFileNames);
	findEcacheMIX(_ecacheFileNames);

	if (_expandFileNames.size() > 0)
		toProcessMixFileNames.insert(toProcessMixFileNames.end(), _expandFileNames.begin(), _expandFileNames.end());
	if (_gameFileNames.size() > 0)
		toProcessMixFileNames.insert(toProcessMixFileNames.end(), _gameFileNames.begin(), _gameFileNames.end());
	if (_ecacheFileNames.size() > 0)
		toProcessMixFileNames.insert(toProcessMixFileNames.end(), _ecacheFileNames.begin(), _ecacheFileNames.end());
	
	if (toProcessMixFileNames.size() > 0)
	{
		for (unsigned int i = 0; i < toProcessMixFileNames.size(); ++i)
		{
			std::cout << "--------------------------------------------------" << std::endl;
			mixHandler->createVirtualMix(toProcessMixFileNames[i]);
		}
		//When all the essential mixes are handled, the search for the child mixes can begin
		findSubGameMIX();
	}
	else
		std::cout << "No MIX files found!" << std::endl;
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
			|| mixFilenames[i] == "MAPS" + GlobalData::MAIN_MissionDisk + "03.MIX"
			|| mixFilenames[i] == "THEME.MIX"		|| mixFilenames[i] == "THEME" + GlobalData::MAIN_MissionDisk + ".MIX"
			|| mixFilenames[i] == "MULTI.MIX"		|| mixFilenames[i] == "MULTI" + GlobalData::MAIN_MissionDisk + ".MIX"
			|| mixFilenames[i] == "LANGUAGE.MIX"	|| mixFilenames[i] == "LANG" + GlobalData::MAIN_MissionDisk + ".MIX")
		{
			filesVector.push_back(mixFilenames[i]);
		}
	}
}

void StartupLoader::findSubGameMIX()
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
			if (checkMixFileInRoot(searchFileName) == true)
			{
				std::cout << "Found in root, creating as parent mix.." << std::endl;
				mixHandler->createVirtualMix(searchFileName);
			}
			else
			{
				// CHECKING IN PROCESSED MIX FILES
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

/*
	Looks for EXPAND(MD)XX.MIX files
	Codewise it looks from 00 -> 99 but the list ends up as 99 -> 00, just like the game does it
*/
void StartupLoader::findExpandMIX(std::vector<std::string>& filesVector)
{
	for (unsigned int i = 0; i < 100; ++i)
	{
		std::stringstream numberStream;
		if (i < 10)
			numberStream << 0 << i;
		else
			numberStream << i;
	
		for (unsigned int j = 0; j < mixFilenames.size(); ++j)
		{
			if (mixFilenames[j] == GlobalData::MAIN_Expand + GlobalData::MAIN_MissionDisk + numberStream.str() + ".MIX")
			{
				//std::cout << "Found 'expandmd' MIX file: " << filenames[j] << std::endl;
				filesVector.insert(filesVector.begin(), mixFilenames[j]);
			}
		}
	}
}

/*
	No specific loading order, this function looks for all ECACHE*.MIX and ELOCAL*.MIX files
	As specified on ModEnc, there's no real order. The list has the same order as Westwood's had, using FindNextFile
*/
void StartupLoader::findEcacheMIX(std::vector<std::string>& filesVector)
{
	for (unsigned int i = 0; i < mixFilenames.size(); ++i)
	{
		if (mixFilenames[i].substr(0, GlobalData::MAIN_Elocal.size()) == GlobalData::MAIN_Elocal)
		{
			//std::cout << "Found 'elocal' MIX file: " << filenames[i] << std::endl;
			filesVector.push_back(mixFilenames[i]);
		}
		else if (mixFilenames[i].substr(0, GlobalData::MAIN_Ecache.size()) == GlobalData::MAIN_Ecache)
		{
			//std::cout << "Found 'ecache' MIX file: " << filenames[i] << std::endl;
			filesVector.push_back(toProcessMixFileNames[i]);
		}
	}
}

void StartupLoader::initiateINI()
{
	WIN32_FIND_DATA ffd;
	std::string installIni = GlobalData::MAIN_InstallDir + GlobalData::MAIN_BackSlash + "*.ini";
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
		std::cout << "Found in DIR: " << fileName << std::endl;
		iniFilenames.push_back(fileName);

		if (!FindNextFile(hFind, &ffd))
			finished = true;
		++i;
	}
	FindClose(hFind);

	findINIFiles();
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
			iniHandler->createVirtualINI(coreIniFiles[i]);
			inRoot = true;
			std::cout << "INI (" << coreIniFiles[i] << ") found in root" << std::endl;
		}
		else
		{
			MixFile* theMix;
			std::string parentMixName;
			if (mixHandler->checkFileInMixes(coreIniFiles[i]))
			{
				parentMixName = mixHandler->getMixNameOfFile(coreIniFiles[i]);
				std::cout << "INI (" << coreIniFiles[i] << ") found in: " << parentMixName << std::endl;
				theMix = mixHandler->getMixByName(parentMixName);
				parentMixName = theMix->getUpperParentName();
				fileOffset = theMix->getAFileOffset(mixHandler->convertNameToID(coreIniFiles[i]));
				fileSize = theMix->getAFileSize(mixHandler->convertNameToID(coreIniFiles[i]));
				
				std::cout << "Upper most MIX from file is: " << parentMixName << std::endl;
				iniHandler->createVirtualINI(coreIniFiles[i], parentMixName, fileOffset, fileSize);
			}
			else
			{
				std::cout << "Unable to find: " << coreIniFiles[i] << " in any MIX!" << std::endl;
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

/*
	TODO IMPORTANT:
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

/*
	Please note: Order is not important here, as it just caches the INI files and later uses them to parse everything
	TODO: Here again, should mission disk from global data be supported for everything?
*/
std::vector<std::string> StartupLoader::getIniNames()
{
	std::vector<std::string> coreIniNames;
	
	//CORE -- MAIN INIs
	coreIniNames.push_back(GlobalData::INI_Rules);
	coreIniNames.push_back(GlobalData::INI_Art);
	coreIniNames.push_back(GlobalData::INI_Sound);
	coreIniNames.push_back(GlobalData::INI_Eva);
	coreIniNames.push_back(GlobalData::INI_Theme);
	coreIniNames.push_back(GlobalData::INI_AI);
	//SP/MP specific INIs
	coreIniNames.push_back(GlobalData::INI_SP_Battle);
	coreIniNames.push_back(GlobalData::INI_MP_Coop);
	coreIniNames.push_back(GlobalData::INI_MP_Modes);
	//coreIniNames.push_back("MAPSEL" +	GlobalData::MIX_missionDisk + ".INI"); // This is no TS!
	//CORE -- THEATERS
	//Loaded only on demand (eg. creating / loading a map)
	//coreIniNames.push_back("SNOW" +		GlobalData::MIX_missionDisk + ".INI");
	//coreIniNames.push_back("TEMPERAT" + GlobalData::MIX_missionDisk + ".INI");
	//coreIniNames.push_back("URBAN" +	GlobalData::MIX_missionDisk + ".INI");
	//coreIniNames.push_back("DESERT" +	GlobalData::MIX_missionDisk + ".INI");
	//coreIniNames.push_back("LUNAR" +	GlobalData::MIX_missionDisk + ".INI");
	//coreIniNames.push_back("URBANN" +	GlobalData::MIX_missionDisk + ".INI");

	return coreIniNames;
}