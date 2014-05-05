#include "stdafx.h"
#include "StartupLoader.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/MixManager.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/CSFManager.hpp"
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
	while (!finished) 
	{
		std::wstring wFileName = ffd.cFileName;
		std::string fileName(wFileName.begin(), wFileName.end());
		std::transform(fileName.begin(), fileName.end(), fileName.begin(), ::toupper);
		mixFilenames.push_back(fileName);

		if (!FindNextFile(hFind, &ffd))
			finished = true;
	}
	FindClose(hFind);
	
	std::vector<std::string>& mixList = getExpandMixes();
	std::vector<std::string>& mainMixes = getMainMixes();
	std::vector<std::string>& subMixes = getSubMixes();
	std::vector<std::string>& ecacheMixes = getEcacheMixes();

	mixList.insert(mixList.end(), mainMixes.begin(), mainMixes.end());
	mixList.insert(mixList.end(), ecacheMixes.begin(), ecacheMixes.end());
	mixList.insert(mixList.end(), subMixes.begin(), subMixes.end());

	if (Config::hasAres)
	{
		mixList.push_back("ARES.MIX");
	}

	for (unsigned int i = 0; i < mixList.size(); ++i)
	{
		//std::cout << "Trying to cache: " << mixList[i] << "." << std::endl;
		MIXManager::getManager()->cache(mixList[i]);
	}
}

void StartupLoader::initiateINI()
{
	WIN32_FIND_DATA ffd;
	std::string installIni = Config::installDir + Config::backSlash + "*.INI";
	std::wstring dir(installIni.begin(), installIni.end());
	const wchar_t* dirChar = dir.c_str();

	HANDLE hFind = FindFirstFile(dirChar, &ffd);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		std::cout << "Invalid INI file!" << std::endl;
	}

	bool finished = false;
	while (!finished)
	{
		std::wstring wFileName = ffd.cFileName;
		std::string fileName(wFileName.begin(), wFileName.end());
		std::transform(fileName.begin(), fileName.end(), fileName.begin(), ::toupper);
		iniFilenames.push_back(fileName);

		if (!FindNextFile(hFind, &ffd))
			finished = true;
	}
	FindClose(hFind);

	std::vector<std::string>& iniFiles = getIniNames();

	for (unsigned int i = 0; i < iniFiles.size(); ++i)
	{
		//std::cout << "Trying to cache: " << iniFiles[i] << std::endl;
		INIManager::getManager()->cache(iniFiles[i]);
	}
}

void StartupLoader::initiateCSF()
{
	WIN32_FIND_DATA ffd;
	std::string installIni = Config::installDir + Config::backSlash + "*.CSF";
	std::wstring dir(installIni.begin(), installIni.end());
	const wchar_t* dirChar = dir.c_str();

	HANDLE hFind = FindFirstFile(dirChar, &ffd);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		std::cout << "Invalid CSF file!" << std::endl;
	}

	bool finished = false;
	while (!finished)
	{
		std::wstring wFileName = ffd.cFileName;
		std::string fileName(wFileName.begin(), wFileName.end());
		std::transform(fileName.begin(), fileName.end(), fileName.begin(), ::toupper);
		csfFilenames.push_back(fileName);

		if (!FindNextFile(hFind, &ffd))
			finished = true;
	}
	FindClose(hFind);

	std::vector<std::string> csfFiles;
	csfFiles.push_back("RA2MD.CSF");
	if (Config::hasAres)
	{
		csfFiles.push_back("ARES.CSF");
		findCSFFiles(csfFiles);
	}

	for (unsigned int i = 0; i < csfFiles.size(); ++i)
	{
		CSFManager::getManager()->cache(csfFiles[i]);
	}
}

void StartupLoader::findCSFFiles(std::vector<std::string>& list)
{
	std::string stringtable = "STRINGTABLE";
	for (unsigned int i = 0; i < 99; ++i)
	{
		std::stringstream number;

		if (i < 10)
		{
			number << '0';
		}
		number << i;

		std::string stringtableNumbered = stringtable + number.str() + ".CSF";

		if (checkCsfInRoot(stringtableNumbered) || MIXManager::getManager()->inAMix(stringtableNumbered))
		{
			list.push_back(stringtableNumbered);
		}
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

bool StartupLoader::checkCsfInRoot(const std::string& fileName)
{
	for (unsigned int i = 0; i < csfFilenames.size(); ++i)
	{
		if (csfFilenames[i] == fileName)
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

	return mainMixNames;
}

/*
	TODO IMPORTANT:
	- Should core mixes also have the modified mission disk name?
	- Currently sticking with 'MD' suffix
*/
std::vector<std::string> StartupLoader::getSubMixes()
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

	coreMixNames.push_back("MAPS01.MIX");
	coreMixNames.push_back("MAPS02.MIX");
	coreMixNames.push_back("MAPSMD03.MIX");

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

	return coreIniNames;
}

std::vector<std::string> StartupLoader::getExpandMixes()
{
	std::vector<std::string> expandMixNames;
	std::stringstream number;

	for (int i = 99; i > -1; --i)
	{
		if (i < 10)
			number << '0';
		number << i;

		std::string& fileNameStr = Config::expand + Config::missionDisk + number.str() + ".MIX";
		if (checkMixFileInRoot(fileNameStr))
		{
			expandMixNames.push_back(fileNameStr);
		}
		number.str(std::string());
	}

	return expandMixNames;
}

std::vector<std::string> StartupLoader::getEcacheMixes()
{
	std::vector<std::string> ecacheMixNames;

	// NOTE: Following code to load ecacheXX.mix files only applies to Tiberian Sun!
	/*std::stringstream number;

	//Ecache 99-00 loop..
	for (int i = 99; i > -1; --i)
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
		if (mixFilenames[i].substr(0, Config::ecache.size()) == Config::ecache)
		{
			// Don't want to put stuff in that's already there...
			if (std::find(ecacheMixNames.begin(), ecacheMixNames.end(), mixFilenames[i]) != ecacheMixNames.end())
				ecacheMixNames.push_back(toProcessMixFileNames[i]);
		}
	}

	// NOTE: The following code to load elocalXX.mix files only applies to Tiberian Sun!

	//Elocal 99-00 loop...
	/*for (int i = 99; i > -1; --i)
	{
		if (i < 10)
			number << '0';
		number << i;

		ecacheMixNames.push_back(Config::elocal + Config::missionDisk + number.str() + ".MIX");
		number.str(std::string());
	}*/

	for (unsigned int i = 0; i < mixFilenames.size(); ++i)
	{
		if (mixFilenames[i].substr(0, Config::elocal.size()) == Config::elocal)
		{
			// Don't want to put stuff in that's already there...
			if (std::find(ecacheMixNames.begin(), ecacheMixNames.end(), mixFilenames[i]) != ecacheMixNames.end())
				ecacheMixNames.push_back(toProcessMixFileNames[i]);
		}
	}

	return ecacheMixNames;
}