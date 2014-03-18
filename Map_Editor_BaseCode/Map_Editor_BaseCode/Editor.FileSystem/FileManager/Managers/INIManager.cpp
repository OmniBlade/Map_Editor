#include "stdafx.h"

#include "INIManager.hpp"
#include "../../../GlobalData.hpp"
#include <iostream>
#include "../FileSystem.hpp"

INIManager::INIManager()
{
	parseConfigFile("CONFIG");
}

INIManager::~INIManager()
{
}

INIFile* INIManager::get(const std::string& fileName)
{
	if (iniFiles[fileName])
		return iniFiles[fileName].get();
	else
		return cache(fileName);
}

INIFile* INIManager::cache(const std::string& fileName)
{
	FileProperties props = FileSystem::getFileSystem()->getFile(fileName);
	if (props.reader)
	{
		iniFiles[fileName] = std::make_unique<INIFile>(props);
		std::cout << "INI: " << fileName << " succesfully cached." << std::endl;
		return iniFiles[fileName].get();
	}
	else
		iniFiles[fileName] = nullptr;
		return nullptr;
}

void INIManager::parseConfigFile(const std::string& _configPath)
{
	std::string CONFIG = "CONFIG";
	iniFiles[CONFIG] = std::make_unique<INIFile>(FileSystem::getFileSystem()->getRootFile(CONFIG));

	std::cout << "Parsing CONFIG..." << std::endl;
	INIFile* configINI = iniFiles[CONFIG].get();
	if (configINI != nullptr)
	{
		INISection* mainSection = configINI->getSection("Main");
		if (mainSection != nullptr)
		{
			GlobalData::MAIN_InstallDir = mainSection->readStringValue("InstallDir", "", true);
			GlobalData::MAIN_MissionDisk = mainSection->readStringValue("MissionDisk", "", true);
			GlobalData::MAIN_Expand = mainSection->readStringValue("ExpandMix", "", true);
			GlobalData::MAIN_Ecache = mainSection->readStringValue("EcacheMix", "", true);
			GlobalData::MAIN_Elocal = mainSection->readStringValue("ElocalMix", "", true);
			GlobalData::MAIN_InGameLighting = mainSection->readBoolValue("InGameLighting", true);
			GlobalData::MAIN_FA2Mode = mainSection->readBoolValue("FA2Mode", false);
		}
		else
			std::cout << "Section [Main] could not be found!" << std::endl;

		INISection* iniSection = configINI->getSection("INI");
		if (iniSection != nullptr)
		{
			GlobalData::INI_Rules = iniSection->readStringValue("Rules", "RULESMD.INI", true);
			GlobalData::INI_Art = iniSection->readStringValue("Art", "ARTMD.INI", true);
			GlobalData::INI_Sound = iniSection->readStringValue("Sound", "SOUNDMD.INI", true);
			GlobalData::INI_Eva = iniSection->readStringValue("Eva", "EVAMD.INI", true);
			GlobalData::INI_Theme = iniSection->readStringValue("Theme", "THEMEMD.INI", true);
			GlobalData::INI_AI = iniSection->readStringValue("AI", "AIDMD.INI", true);
			GlobalData::INI_SP_Battle = iniSection->readStringValue("Battle", "BATTLEMD.INI", true);
			GlobalData::INI_MP_Modes = iniSection->readStringValue("Modes", "MPMODESMD.INI", true);
			GlobalData::INI_MP_Coop = iniSection->readStringValue("Coop", "COOPCAMPMD.INI", true);
		}
		else
			std::cout << "Section [INI] could not be found!" << std::endl;
	}
	else
		std::cout << "CONFIG could not be found in the editor root!" << std::endl;	
}