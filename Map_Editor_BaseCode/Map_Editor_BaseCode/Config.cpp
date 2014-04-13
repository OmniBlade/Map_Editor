#include "stdafx.h"
#include "Config.hpp"
#include "Log.hpp"
#include "Editor.FileSystem\FileManager\Managers\INIManager.hpp"
#include "Editor.FileSystem\IniFile\INIFile.hpp"

// This is FIXED for Red Alert 2 and Yuri's Revenge. Only changed for TS/FS
unsigned int Config::tileWidth = 60;
unsigned int Config::tileHeight = 30;

// [MAIN]
std::string Config::editorRoot = "";
std::string Config::installDir = "";
std::string Config::backSlash = "\\";
std::string Config::missionDisk = "MD";
std::string Config::expand = "EXPAND";
std::string Config::ecache = "ECACHE";
std::string Config::elocal = "ELOCAL";
bool Config::inGameLighting = true;
bool Config::FA2Mode = false;

// [INI]
std::string Config::rules	= "RULESMD.INI";
std::string Config::art		= "ARTMD.INI";
std::string Config::sound	= "SOUNDMD.INI";
std::string Config::eva		= "EVAMD.INI";
std::string Config::theme	= "THEMEMD.INI";
std::string Config::AI		= "AIMD.INI";
std::string Config::battle	= "BATTLEMD.INI";
std::string Config::modes	= "MPMODESMD.INI";
std::string Config::coop	= "COOPCAMPMD.INI";

void Config::parse()
{
	Log::line("Parsing CONFIG file...", Log::INFO);
	
	std::string CONFIG = "CONFIG";
	INIFile* configINI = INIManager::getManager()->get(CONFIG);

	if (configINI != nullptr)
	{
		INISection* mainSection = configINI->getSection("Main");
		if (mainSection != nullptr)
		{
			//Temporary uglyness, to support 3 separate directories
			std::string installDir1 = mainSection->readStringValue("InstallDir", "", true);
			std::string installDir2 = mainSection->readStringValue("InstallDir2", "", true);
			std::string installDir3 = mainSection->readStringValue("InstallDir3", "", true);

			BinaryReader dir1(installDir1 + "\\" + "GAMEMD.EXE");
			BinaryReader dir2(installDir2 + "\\" + "GAMEMD.EXE");
			BinaryReader dir3(installDir3 + "\\" + "GAMEMD.EXE");

			if (dir1.isOpened)
				Config::installDir = installDir1;
			else if (dir2.isOpened)
				Config::installDir = installDir2;
			else
				Config::installDir = installDir3;

			//Config::MAIN_InstallDir = mainSection->readStringValue("InstallDir", "", true);
			Config::missionDisk = mainSection->readStringValue("MissionDisk", "", true);
			Config::expand = mainSection->readStringValue("ExpandMix", "", true);
			Config::ecache = mainSection->readStringValue("EcacheMix", "", true);
			Config::elocal = mainSection->readStringValue("ElocalMix", "", true);
			Config::inGameLighting = mainSection->readBoolValue("InGameLighting", true);
			Config::FA2Mode = mainSection->readBoolValue("FA2Mode", false);
		}
		else
			Log::line("Section [Main] could not be found!", Log::CRITICAL);

		INISection* iniSection = configINI->getSection("INI");
		if (iniSection != nullptr)
		{
			Config::rules = iniSection->readStringValue("Rules", "RULESMD.INI", true);
			Config::art = iniSection->readStringValue("Art", "ARTMD.INI", true);
			Config::sound = iniSection->readStringValue("Sound", "SOUNDMD.INI", true);
			Config::eva = iniSection->readStringValue("Eva", "EVAMD.INI", true);
			Config::theme = iniSection->readStringValue("Theme", "THEMEMD.INI", true);
			Config::AI = iniSection->readStringValue("AI", "AIDMD.INI", true);
			Config::battle = iniSection->readStringValue("Battle", "BATTLEMD.INI", true);
			Config::modes = iniSection->readStringValue("Modes", "MPMODESMD.INI", true);
			Config::coop = iniSection->readStringValue("Coop", "COOPCAMPMD.INI", true);
		}
		else
			Log::line("Section [INI] could not be found!", Log::ERRORS);
	}
	else
		Log::line("CONFIG could not be found in the editor root!", Log::CRITICAL);
}