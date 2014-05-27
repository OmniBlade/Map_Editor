#include "stdafx.h"
#include "Config.hpp"
#include "Log.hpp"
#include "Editor.FileSystem\FileManager\Managers\INIManager.hpp"
#include "Editor.FileSystem\IniFile\INISection.hpp"

// This is FIXED for Red Alert 2 and Yuri's Revenge. Only changed for TS/FS
unsigned int Config::tileWidth = 60;
unsigned int Config::tileHeight = 30;
int Config::language = -1;
std::string Config::configName = "";
bool Config::enableDebug = false;
bool Config::dumpTypes = false;
std::string Config::mapName = "";

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

// [GameExtension]
bool Config::hasAres = false;

void Config::parse(INIFile* configINI, const std::string& name)
{
	Log::note();
	Log::note("Showing configuration file flags below:", Log::DEBUG);
	configName = name;
	if (configINI != nullptr)
	{
		INISection* mainSection = configINI->getSection("Main");
		if (mainSection != nullptr)
		{
			mainSection->readStringValue("InstallDir", Config::installDir, "", true);
			Log::note("Install directory: " + installDir, Log::DEBUG);
			mainSection->readStringValue("MissionDisk", Config::missionDisk, "MD", true);
			Log::note("Mission disk: " + missionDisk, Log::DEBUG);
			mainSection->readStringValue("ExpandMix", Config::expand, "EXPAND", true);
			Log::note("Expand: " + expand, Log::DEBUG);
			mainSection->readStringValue("EcacheMix", Config::ecache, "ECACHE", true);
			Log::note("Ecache: " + ecache, Log::DEBUG);
			mainSection->readStringValue("ElocalMix", Config::elocal, "ELOCAL", true);
			Log::note("Elocal: " + elocal, Log::DEBUG);
			mainSection->readBoolValue("InGameLighting", Config::inGameLighting, true);
			Log::note("In-game lighting: " + Log::toString(inGameLighting), Log::DEBUG);
			mainSection->readBoolValue("FA2Mode", Config::FA2Mode, false);
			Log::note("FA2 mode: " + Log::toString(FA2Mode), Log::DEBUG);
		}
		else
			Log::note("Section [Main] could not be found!", Log::DEBUG);

		INISection* iniSection = configINI->getSection("INI");
		if (iniSection != nullptr)
		{
			iniSection->readStringValue("Rules", Config::rules, "RULESMD.INI", true);
			Log::note("Rules: " + rules, Log::DEBUG);
			iniSection->readStringValue("Art", Config::art, "ARTMD.INI", true);
			Log::note("Art: " + art, Log::DEBUG);
			iniSection->readStringValue("Sound", Config::sound, "SOUNDMD.INI", true);
			Log::note("Sound: " + sound, Log::DEBUG);
			iniSection->readStringValue("Eva", Config::eva, "EVAMD.INI", true);
			Log::note("Eva: " + eva, Log::DEBUG);
			iniSection->readStringValue("Theme", Config::theme, "THEMEMD.INI", true);
			Log::note("Theme: " + theme, Log::DEBUG);
			iniSection->readStringValue("AI", Config::AI, "AIDMD.INI", true);
			Log::note("AI: " + AI, Log::DEBUG);
			iniSection->readStringValue("Battle", Config::battle, "BATTLEMD.INI", true);
			Log::note("Battle: " + battle, Log::DEBUG);
			iniSection->readStringValue("Modes", Config::modes, "MPMODESMD.INI", true);
			Log::note("Modes: " + modes, Log::DEBUG);
			iniSection->readStringValue("Coop", Config::coop, "COOPCAMPMD.INI", true);
			Log::note("Coop: " + coop, Log::DEBUG);
		}
		else
			Log::note("Section [INI] could not be found!", Log::DEBUG);

		INISection* extensionSection = configINI->getSection("GameExtension");
		if (extensionSection != nullptr)
		{
			extensionSection->readBoolValue("Ares", Config::hasAres);
			Log::note("Ares: " + Log::toString(hasAres), Log::DEBUG);
		}
		else
			Log::note("Section [GameExtension] could not be found!", Log::DEBUG);
	}
	else
		Log::note(name + " could not be found in the editor root!", Log::DEBUG);

	Log::note("End of configuration file flags.", Log::DEBUG);
}