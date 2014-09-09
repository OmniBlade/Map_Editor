#include "stdafx.h"
#include "StartupLoader.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/MixManager.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/CSFManager.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../Config.hpp"
#include "../../Log.hpp"
#include "../../GameDefinition.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <windows.h>

StartupLoader::StartupLoader()
{

}

void StartupLoader::initiateMIX()
{
	std::vector<std::string> mixFilenames = getFilesWithExtension("MIX");
	std::vector<std::string> mixList;

	//Only load additional mixes if it is set
	if (!Config::extraMix.empty())
	{
		LineSplitter extraMixes(Config::extraMix);
		unsigned int extraMixesAmount = extraMixes.size();
		for (unsigned int i = 0; i < extraMixesAmount; ++i)
		{
			mixList.push_back(extraMixes.pop_string());
		}
	}
		
	std::vector<std::string>& expandMixes = getExpandMixes(mixFilenames);
	std::vector<std::string>& mainMixes = getMainMixes();
	std::vector<std::string>& subMixes = getSubMixes();
	std::vector<std::string>& ecacheMixes = getEcacheMixes();

	mixList.insert(mixList.end(), expandMixes.begin(), expandMixes.end());
	mixList.insert(mixList.end(), mainMixes.begin(), mainMixes.end());
	mixList.insert(mixList.end(), ecacheMixes.begin(), ecacheMixes.end());
	mixList.insert(mixList.end(), subMixes.begin(), subMixes.end());

	if (Config::hasAres)
	{
		mixList.push_back("ARES.MIX");
	}

	//Finally cache everything
	for (unsigned int i = 0; i < mixList.size(); ++i)
	{
		MIXManager::getManager()->cache(mixList[i]);
	}
}

void StartupLoader::initiateINI()
{
	std::vector<std::string> iniFilenames = getFilesWithExtension("INI");

	std::vector<std::string>& iniFiles = getIniNames();
	INIManager* iniManager = INIManager::getManager();

	//Finally cache everything
	for (unsigned int i = 0; i < iniFiles.size(); ++i)
	{
		iniManager->cache(iniFiles[i]);
	}

	iniManager->cacheRoot("PARAMS");
	iniManager->cacheRoot("ACTIONS");
	iniManager->cacheRoot("EVENTS");
	iniManager->cacheRoot("ACTIONS_S");
}

void StartupLoader::initiateCSF()
{
	std::vector<std::string> csfFilenames = getFilesWithExtension("CSF");

	std::vector<std::string> csfFiles;
	if (Config::hasAres)
	{
		findCSFFiles(csfFiles, csfFilenames);
	}

	if (Game::title == Game::Type::Base)
		csfFiles.push_back("RA2.CSF");
	else if (Game::title == Game::Type::Expansion)
		csfFiles.push_back("RA2MD.CSF");

	if (Config::hasAres)
	{
		csfFiles.push_back("ARES.CSF");
	}

	//Finally cache everything
	for (unsigned int i = 0; i < csfFiles.size(); ++i)
	{
		CSFManager::getManager()->cache(csfFiles[i]);
	}
}

/*
	ARES ONLY
*/
void StartupLoader::findCSFFiles(std::vector<std::string>& list, const std::vector<std::string>& csfFilenames)
{
	std::string stringtable = "STRINGTABLE";
	for (int i = 99; i > -1; --i)
	{
		std::stringstream number;

		if (i < 10)
		{
			number << '0';
		}
		number << i;

		std::string stringtableNumbered = stringtable + number.str() + ".CSF";

		if (inRoot(stringtableNumbered, csfFilenames) || MIXManager::getManager()->inAMix(stringtableNumbered))
		{
			list.push_back(stringtableNumbered);
		}
	}
}

bool StartupLoader::inRoot(const std::string& fileName, const std::vector<std::string>& filenames)
{
	for (unsigned int i = 0; i < filenames.size(); ++i)
	{
		if (filenames[i] == fileName)
			return true;
	}
	return false;
}

std::vector<std::string> StartupLoader::getMainMixes()
{
	std::vector<std::string> mainMixNames;

	if (Game::title == Game::Type::Expansion)
		mainMixNames.push_back("LANGMD.MIX");
	mainMixNames.push_back("LANGUAGE.MIX");
	
	if (Game::title == Game::Type::Expansion)
		mainMixNames.push_back("RA2MD.MIX");
	mainMixNames.push_back("RA2.MIX");
	
	if (Game::title == Game::Type::Expansion)
		mainMixNames.push_back("CACHEMD.MIX");
	mainMixNames.push_back("CACHE.MIX");
	
	if (Game::title == Game::Type::Expansion)
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

	std::cout << "WARNING! THEATER MIX NAMES ARE ONLY SUPPORTED FOR YR,\nREMOVE DEPENDENCY AND MOVE TO CONFIG FILE FOR THEATERS" << std::endl;
	std::cout << "ISOGEN HAS TO BE LOADED FOR BOTH GAMES!" << std::endl;

	/*
		RA2's list for files is COMPLETELY different than YR's
	*/
	if (Game::title == Game::Type::Base)
	{
		coreMixNames.push_back("CONQUER.MIX");
		coreMixNames.push_back("MAPS01.MIX");
		coreMixNames.push_back("MAPS02.MIX");
		//Theater shit
		//Temperate
		coreMixNames.push_back("TEMPERAT.MIX");
		coreMixNames.push_back("TEM.MIX");
		coreMixNames.push_back("ISOTEMP.MIX");
		//Snow
		coreMixNames.push_back("SNOW.MIX");
		coreMixNames.push_back("SNO.MIX");
		coreMixNames.push_back("ISOSNOW.MIX");
		//Urban
		coreMixNames.push_back("URBAN.MIX");
		coreMixNames.push_back("URB.MIX");
		coreMixNames.push_back("ISOURB.MIX");

		coreMixNames.push_back("GENERIC.MIX");
		coreMixNames.push_back("ISOGEN.MIX");

	}
	else if (Game::title == Game::Type::Expansion)
	{
		coreMixNames.push_back("CONQMD.MIX");
		coreMixNames.push_back("GENERMD.MIX");

		coreMixNames.push_back("GENERIC.MIX");
		coreMixNames.push_back("ISOGENMD.MIX");
		coreMixNames.push_back("ISOGEN.MIX");
		coreMixNames.push_back("CONQUER.MIX");
		//Theater shit
		//Temperate
		coreMixNames.push_back("TEMPERATMD.MIX");
		coreMixNames.push_back("TEM.MIX");
		coreMixNames.push_back("ISOTEMMD.MIX");
		coreMixNames.push_back("ISOTEMP.MIX");
		//Snow
		coreMixNames.push_back("SNOWMD.MIX");
		coreMixNames.push_back("SNO.MIX");
		coreMixNames.push_back("ISOSNOMD.MIX");
		coreMixNames.push_back("ISOSNOW.MIX");
		//Urban
		coreMixNames.push_back("URBANMD.MIX");
		coreMixNames.push_back("URB.MIX");
		coreMixNames.push_back("ISOURBMD.MIX");
		coreMixNames.push_back("ISOURB.MIX");
		//Desert
		coreMixNames.push_back("DESERTMD.MIX");
		coreMixNames.push_back("DES.MIX");
		coreMixNames.push_back("ISODESMD.MIX");
		coreMixNames.push_back("ISODES.MIX");
		//New Urban
		coreMixNames.push_back("URBANNMD.MIX");
		coreMixNames.push_back("UBN.MIX");
		coreMixNames.push_back("ISOUBN.MIX");
		coreMixNames.push_back("ISOUBNMD.MIX");
		//Lunar
		coreMixNames.push_back("LUNDARMD.MIX");
		coreMixNames.push_back("LUN.MIX");
		coreMixNames.push_back("ISOLUNMD.MIX");
		coreMixNames.push_back("ISOLUN.MIX");

		coreMixNames.push_back("MAPS01.MIX");
		coreMixNames.push_back("MAPS02.MIX");
		coreMixNames.push_back("MAPSMD03.MIX");
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
	coreIniNames.push_back(Config::rules);
	coreIniNames.push_back(Config::art);
	coreIniNames.push_back(Config::sound);
	coreIniNames.push_back(Config::eva);
	coreIniNames.push_back(Config::theme);
	coreIniNames.push_back(Config::AI);
	coreIniNames.push_back(Config::UI);
	//SP/MP specific INIs
	coreIniNames.push_back(Config::battle);
	coreIniNames.push_back(Config::coop);
	coreIniNames.push_back(Config::modes);

	return coreIniNames;
}

std::vector<std::string> StartupLoader::getExpandMixes(const std::vector<std::string>& mixFilenames)
{
	std::vector<std::string> expandMixNames;
	std::stringstream number;

	// Prefix for getting the left hand side of the filename only once instead of every loop
	std::string prefix;
	if (Game::title == Game::Type::Base)
		prefix = Config::expand;
	else if (Game::title == Game::Type::Expansion)
		prefix = Config::expand + Config::missionDisk;
	
	for (int i = 99; i > -1; --i)
	{
		if (i < 10)
			number << '0';
		number << i;

		std::string fileNameStr;
		fileNameStr = prefix + number.str() + ".MIX";
		
		if (inRoot(fileNameStr, mixFilenames))
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
			if (std::find(ecacheMixNames.begin(), ecacheMixNames.end(), mixFilenames[i]) == ecacheMixNames.end())
			{
				ecacheMixNames.push_back(mixFilenames[i]);
			}
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
			if (std::find(ecacheMixNames.begin(), ecacheMixNames.end(), mixFilenames[i]) == ecacheMixNames.end())
				ecacheMixNames.push_back(mixFilenames[i]);
		}
	}

	return ecacheMixNames;
}

std::vector<std::string> StartupLoader::getFilesWithExtension(const std::string& ext)
{
	std::vector<std::string> filenames;

	WIN32_FIND_DATA ffd;
	std::string installIni = Config::installDir + Config::backSlash + "*." + ext;
	std::wstring dir(installIni.begin(), installIni.end());
	const wchar_t* dirChar = dir.c_str();

	HANDLE hFind = FindFirstFile(dirChar, &ffd);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		std::cout << "Invalid " << ext << " file!" << std::endl;
	}

	bool finished = false;
	while (!finished)
	{
		std::wstring wFileName = ffd.cFileName;
		std::string fileName(wFileName.begin(), wFileName.end());
		std::transform(fileName.begin(), fileName.end(), fileName.begin(), ::toupper);
		filenames.push_back(fileName);

		if (!FindNextFile(hFind, &ffd))
			finished = true;
	}
	FindClose(hFind);

	return filenames;
}
