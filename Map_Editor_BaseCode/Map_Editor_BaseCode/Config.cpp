#include "stdafx.h"
#include "Config.hpp"
#include "Log.hpp"
#include "GameDefinition.h"
#include "Editor.FileSystem\FileManager\Managers\INIManager.hpp"
#include "Editor.FileSystem\IniFile\INISection.hpp"

// This is FIXED for Red Alert 2 and Yuri's Revenge. Only changed for TS/FS
unsigned int Config::tileWidth = 60;
unsigned int Config::tileHeight = 30;
int Config::language = -1;
std::string Config::configName = "";
bool Config::enableDebug = false;
bool Config::dumpTypes = false;
bool Config::isSP = false;
std::string Config::mapName = "";

// [MAIN]
std::string Config::editorRoot = "";
std::string Config::installDir = "";
std::string Config::executable = "GAMEMD.EXE";
std::string Config::backSlash = "\\";
std::string Config::missionDisk = "MD";
std::string Config::expand = "EXPAND";
std::string Config::ecache = "ECACHE";
std::string Config::elocal = "ELOCAL";
std::string Config::extraMix = "";
bool Config::inGameLighting = true;
bool Config::FA2Mode = false;
bool Config::AIReferences = false;

// [INI]
std::string Config::rules	= "RULESMD.INI";
std::string Config::art		= "ARTMD.INI";
std::string Config::sound	= "SOUNDMD.INI";
std::string Config::eva		= "EVAMD.INI";
std::string Config::theme	= "THEMEMD.INI";
std::string Config::AI		= "AIMD.INI";
std::string Config::UI		= "UIMD.INI";
std::string Config::battle	= "BATTLEMD.INI";
std::string Config::modes	= "MPMODESMD.INI";
std::string Config::coop	= "COOPCAMPMD.INI";

// [GameExtension]
bool Config::hasAres = false;

void Config::parse(INIFile* configINI)
{
	Log::note();
	Log::note("Showing configuration file flags below:", Log::DEBUG);
	if (configINI != nullptr)
	{
		if (INISection* mainSection = configINI->getSection("Main"))
		{
			std::string defE;
			if (Game::title == Game::Type::Base)
			{
				defE = "GAME.EXE";
			}
			else
			{
				defE = "GAMEMD.EXE";
			}

			mainSection->readStringValue("Executable", Config::executable, defE, true);
			if (Game::title == Game::Type::Expansion)
			{
				mainSection->readStringValue("MissionDisk", Config::missionDisk, "MD", true);
			}
			mainSection->readStringValue("ExtraMixes", Config::extraMix, "", true);
			mainSection->readStringValue("ExpandMix", Config::expand, "EXPAND", true);
			mainSection->readStringValue("EcacheMix", Config::ecache, "ECACHE", true);
			mainSection->readStringValue("ElocalMix", Config::elocal, "ELOCAL", true);
		}
		else
		{
			Log::note("Section [Main] (" + configName + ") could not be found! Using defaults.", Log::DEBUG);
			if (Game::title == Game::Type::Base)
			{
				executable = "GAME.EXE";
			}
		}
		
		Log::note("Install directory: " + installDir, Log::DEBUG);
		Log::note("Executable name: " + executable, Log::DEBUG);
		Log::note("Expand: " + expand, Log::DEBUG);
		Log::note("Ecache: " + ecache, Log::DEBUG);
		Log::note("Elocal: " + elocal, Log::DEBUG);
		if (Game::title == Game::Type::Expansion)
			Log::note("Mission disk: " + missionDisk, Log::DEBUG);

		if (INISection* iniSection = configINI->getSection("INI"))
		{
			std::string defR, defA, defS, defE, defT, defAI, defU, defB, defM, defC;
			if (Game::title == Game::Type::Base)
			{
				defR = "RULES.INI";
				defA = "ART.INI";
				defS = "SOUND.INI";
				defE = "EVA.INI";
				defT = "THEME.INI";
				defAI = "AI.INI";
				defU = "UI.INI";
				defB = "BATTLE.INI";
				defM = "MPMODES.INI";
				defC = "COOPCAMP.INI";
			}
			else
			{
				defR = "RULESMD.INI";
				defA = "ARTMD.INI";
				defS = "SOUNDMD.INI";
				defE = "EVAMD.INI";
				defT = "THEMEMD.INI";
				defAI = "AIMD.INI";
				defU = "UIMD.INI";
				defB = "BATTLEMD.INI";
				defM = "MPMODESMD.INI";
				defC = "COOPCAMPMD.INI";
			}

			iniSection->readStringValue("Rules", Config::rules, defR, true);
			iniSection->readStringValue("Art", Config::art, defA, true);
			iniSection->readStringValue("Sound", Config::sound, defS, true);
			iniSection->readStringValue("Eva", Config::eva, defE, true);
			iniSection->readStringValue("Theme", Config::theme, defT, true);
			iniSection->readStringValue("AI", Config::AI, defAI, true);
			iniSection->readStringValue("UI", Config::UI, defU, true);
			iniSection->readStringValue("Battle", Config::battle, defB, true);
			iniSection->readStringValue("Modes", Config::modes, defM, true);
			iniSection->readStringValue("Coop", Config::coop, defC, true);
		}
		else
		{
			Log::note("Section [INI] could not be found! Using defaults.", Log::DEBUG);
			if (Game::title == Game::Type::Base)
			{
				rules = "RULES.INI";
				art = "ART.INI";
				sound = "SOUND.INI";
				eva = "EVA.INI";
				theme = "THEME.INI";
				AI = "AI.INI";
				UI = "UI.INI";
				battle = "BATTLE.INI";
				modes = "MPMODES.INI";
				coop = "COOPCAMP.INI";
			}

		}
		Log::note("Rules: " + rules, Log::DEBUG);
		Log::note("Art: " + art, Log::DEBUG);
		Log::note("Sound: " + sound, Log::DEBUG);
		Log::note("Eva: " + eva, Log::DEBUG);
		Log::note("Theme: " + theme, Log::DEBUG);
		Log::note("AI: " + AI, Log::DEBUG);
		Log::note("UI: " + UI, Log::DEBUG);
		Log::note("Battle: " + battle, Log::DEBUG);
		Log::note("Modes: " + modes, Log::DEBUG);
		Log::note("Coop: " + coop, Log::DEBUG);

		if (Game::title == Game::Type::Expansion)
		{
			if (INISection* extensionSection = configINI->getSection("GameExtension"))
			{
				extensionSection->readBoolValue("Ares", Config::hasAres);
			}
			else
			{
				Log::note("Section [GameExtension] could not be found! Using defaults.", Log::DEBUG);
				hasAres = false;
			}
			Log::note("Ares: " + Log::toString(hasAres), Log::DEBUG);
		}
	}
	else
		Log::note(configName + " could not be found in the editor root!", Log::DEBUG);

	Log::note("End of configuration file flags.", Log::DEBUG);
}