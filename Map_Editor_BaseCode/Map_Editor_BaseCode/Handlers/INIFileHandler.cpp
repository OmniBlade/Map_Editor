#include "stdafx.h"
#include "INIFileHandler.hpp"
#include "../GlobalData.hpp"
#include <iostream>

INIFileHandler::INIFileHandler()
{
}


INIFileHandler::~INIFileHandler()
{
}

void INIFileHandler::createVirtualINI(const std::string& _ININame, const std::string& parentName /* = "" */, __int32 offset /* = 0 */, int size /* = 0 */)
{
	if (parentName != "")
	{
		currentINI = new INIFile(_ININame, parentName, offset, size);
	}
	else
	{
		currentINI = new INIFile(_ININame);
	}
	iniFiles.push_back(currentINI);
}

INIFile* INIFileHandler::getAnINIFile(const std::string& _ININame)
{
	for (unsigned int i = 0; i < iniFiles.size(); ++i)
	{
		if (iniFiles[i]->getININame() == _ININame)
			return iniFiles[i];
	}
	std::cout << "WARNING - Correct INI File could not be located (" << _ININame << "), returning front of vector!" << std::endl;
	return iniFiles.front();
}

void INIFileHandler::parseConfigFile(const std::string& _configPath)
{
	std::cout << "Parsing CONFIG..." << std::endl;
	iniFiles.push_back(new INIFile("CONFIG", _configPath));
	//createVirtualINI(configName);
	INIFile* configINI = getAnINIFile("CONFIG");
	
	if (configINI != nullptr)
	{
		std::cout << "Getting section pointer" << std::endl;
		INISection* mainSection = configINI->getSection("Main");
		if (mainSection != nullptr)
		{
			GlobalData::MAIN_InstallDir =		mainSection->readStringValue("InstallDir", "", true);
			GlobalData::MAIN_MissionDisk =		mainSection->readStringValue("MissionDisk", "", true);
			GlobalData::MAIN_Expand =			mainSection->readStringValue("ExpandMix", "", true);
			GlobalData::MAIN_Ecache =			mainSection->readStringValue("EcacheMix", "", true);
			GlobalData::MAIN_Elocal =			mainSection->readStringValue("ElocalMix", "", true);
			GlobalData::MAIN_InGameLighting =	mainSection->readBoolValue("InGameLighting", true);
			GlobalData::MAIN_FA2Mode =			mainSection->readBoolValue("FA2Mode", false);
		}
		else
			std::cout << "Section [Main] could not be found!" << std::endl;

		INISection* iniSection = configINI->getSection("INI");
		if (iniSection != nullptr)
		{
			GlobalData::INI_Rules =		iniSection->readStringValue("Rules", "RULESMD.INI", true);
			GlobalData::INI_Art =		iniSection->readStringValue("Art", "ARTMD.INI", true);
			GlobalData::INI_Sound =		iniSection->readStringValue("Sound", "SOUNDMD.INI", true);
			GlobalData::INI_Eva =		iniSection->readStringValue("Eva", "EVAMD.INI", true);
			GlobalData::INI_Theme =		iniSection->readStringValue("Theme", "THEMEMD.INI", true);
			GlobalData::INI_AI =		iniSection->readStringValue("AI", "AIDMD.INI", true);
			GlobalData::INI_SP_Battle = iniSection->readStringValue("Battle", "BATTLEMD.INI", true);
			GlobalData::INI_MP_Modes =	iniSection->readStringValue("Modes", "MPMODESMD.INI", true);
			GlobalData::INI_MP_Coop =	iniSection->readStringValue("Coop", "COOPCAMPMD.INI", true);
		}
		else
			std::cout << "Section [INI] could not be found!" << std::endl;
	}
	else
		std::cout << "CONFIG could not be found in the direct root!" << std::endl;
}