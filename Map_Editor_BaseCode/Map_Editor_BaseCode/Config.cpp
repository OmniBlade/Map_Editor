#include "stdafx.h"
#include "Config.hpp"
#include "Log.hpp"
#include "GameDefinition.h"
#include "Editor.FileSystem\FileManager\Managers\INIManager.hpp"
#include "Editor.FileSystem\IniFile\INISection.hpp"
#include "Editor.FileSystem\MapFile\WriterHelper.h"

// This is FIXED for Red Alert 2 and Yuri's Revenge. Only changed for TS/FS
const unsigned int Config::tileWidth = 60;
const unsigned int Config::tileHeight = 30;
int Config::language = -1;
std::string Config::configName = "";
bool Config::enableDebug = false;
bool Config::dumpTypes = false;
bool Config::explicitOverlayTypeValidation = false;
bool Config::isSP = false;
std::string Config::mapName = "";

// [MAIN]
std::string Config::name = "Unknown: RA2, YR?";
std::string Config::editorRoot = "";
std::string Config::installDir = "";
std::string Config::executable = "GAMEMD.EXE";
std::string Config::backSlash = "\\";
std::string const Config::mapModsName = ".%.MM.%.";
std::string Config::missionDisk = "MD";
std::string Config::expand = "EXPAND";
std::string Config::ecache = "ECACHE";
std::string Config::elocal = "ELOCAL";
std::string Config::extraMix = "";
bool Config::inGameLighting = true;
bool Config::FA2Mode = false;
bool Config::AIReferences = false;
bool Config::ObsoleteSettings = false;


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

void Config::parse(INIFile* configINI, const std::string& nameDefault)
{
	if (!nameDefault.empty())
	{
		name = nameDefault;
		Log::line("Setting up editor for: " + nameDefault + ".", Log::DEBUG);
	}

	if (configINI != nullptr)
	{
		if (INISection* mainSection = configINI->getSection("Main"))
		{
			std::string defE, defN;
			if (Game::title == Game::Type::Base)
			{
				defE = "GAME.EXE";
				defN = "Red Alert 2";
			}
			else
			{
				defE = "GAMEMD.EXE";
				defN = "Yuri's Revenge";
			}

			mainSection->readStringValue("Name", Config::name, defN, false);
			if(!nameDefault.empty()) mainSection->readStringValue("Executable", Config::executable, defN, true);
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
			Log::line("Section [Main] (" + configName + ") could not be found! Using defaults.", Log::DEBUG);
			if (Game::title == Game::Type::Base)
			{
				if(!nameDefault.empty()) name = "Red Alert 2";
				executable = "GAME.EXE";
			}
			else if (Game::title == Game::Type::Expansion)
			{
				if(!nameDefault.empty()) name = "Yuri's Revenge";
			}
		}
		

		if (nameDefault.empty())
		{
			Log::line("Setting up editor for: " + name + ".", Log::DEBUG);
		}

		Log::line();
		Log::line("Showing configuration file flags below:", Log::DEBUG);


		Log::line("Install directory is: " + installDir, Log::DEBUG);
		Log::line("Executable name: " + executable, Log::DEBUG);
		Log::line("Expand: " + expand, Log::DEBUG);
		Log::line("Ecache: " + ecache, Log::DEBUG);
		Log::line("Elocal: " + elocal, Log::DEBUG);
		if (Game::title == Game::Type::Expansion)
			Log::line("Mission disk: " + missionDisk, Log::DEBUG);

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
			Log::line("Section [INI] could not be found! Using defaults.", Log::DEBUG);
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
		Log::line("Rules: " + rules, Log::DEBUG);
		Log::line("Art: " + art, Log::DEBUG);
		Log::line("Sound: " + sound, Log::DEBUG);
		Log::line("Eva: " + eva, Log::DEBUG);
		Log::line("Theme: " + theme, Log::DEBUG);
		Log::line("AI: " + AI, Log::DEBUG);
		Log::line("UI: " + UI, Log::DEBUG);
		Log::line("Battle: " + battle, Log::DEBUG);
		Log::line("Modes: " + modes, Log::DEBUG);
		Log::line("Coop: " + coop, Log::DEBUG);

		if (Game::title == Game::Type::Expansion)
		{
			if (INISection* extensionSection = configINI->getSection("GameExtension"))
			{
				extensionSection->readBoolValue("Ares", Config::hasAres);
			}
			else
			{
				Log::line("Section [GameExtension] could not be found! Using defaults.", Log::DEBUG);
				hasAres = false;
			}
			Log::line("Ares: " + BoolWriter::getBoolString(hasAres, BoolWriter::BoolType::YESNO), Log::DEBUG);
		}
	}
	else
		Log::line(configName + " could not be found in the editor root!", Log::DEBUG);

	Log::line("End of configuration file flags.", Log::DEBUG);
}