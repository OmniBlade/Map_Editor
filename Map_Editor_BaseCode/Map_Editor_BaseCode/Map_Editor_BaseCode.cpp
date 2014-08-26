// ConsoleApplication1.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Editor.FileSystem/FileManager/FileSystem.hpp"
#include "Editor.FileSystem/FileManager/RawFileSystem.hpp"
#include "Editor.FileSystem/FileManager/Managers/INIManager.hpp"	
#include "Editor.FileSystem/FileManager/Managers/MIXmanager.hpp"	
#include "Editor.FileSystem/FileManager/Managers/CSFManager.hpp"	
#include "Editor.FileSystem/FileManager/FileSystem.hpp"
#include "Editor.Engine/Loading/StartupLoader.hpp"		
#include "Editor.Engine/Map/TheaterCollection.hpp"
#include "Editor.FileSystem/INIFile/INIFile.hpp"
#include "Editor.FileSystem/IniFile/INISection.hpp"
#include "Editor.Engine/Loading/MapLoader.hpp"
#include "Editor.Engine/Loading/MapAssetLoader.hpp"
#include "Editor.Configuration/ConfigLoader.hpp"
#include "Editor.Engine\Game\GameModeCollection.hpp"
#include "Editor.Map.Validator\MainValidator.hpp"
#include "Editor.Engine\Basics\Basic.hpp"
#include "Editor.FileSystem\MapFile\ParamCollection.hpp"
#include "Editor.FileSystem\MapFile\SActionCollection.hpp"
#include "Editor.FileSystem\MapFile\ActionCollection.hpp"
#include "Editor.FileSystem\MapFile\EventCollection.hpp"
#include "Editor.Engine\Map\IsoMapPack.hpp"
#include "Editor.Engine\Map\OverlayDataPack.hpp"
#include "Editor.FileSystem\FileManager\Managers\EncManager.hpp"
#include "Editor.FileSystem\EncFile\EncFile.hpp"
#include "Config.hpp"
#include "Arguments.hpp"
#include "Log.hpp"
#include <cstdlib>
#include <Windows.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

void initiateEditor()
{
	//TODO: Rename ambiguous functions
	RawFileSystem* rawSystem = new RawFileSystem();;
	MIXManager::getManager()->assign(rawSystem);
	FileSystem::getFileSystem()->assign(rawSystem);

	ConfigLoader configLoader;
	if (!configLoader.chooseConfig())
	{
		Log::close();
		std::cin.get();
		exit(0);
	}

	if (Config::installDir.empty())
	{
		Log::note("Unable to determine install directory, terminating now...", Log::DEBUG);
		Log::close();
		system("pause");
		exit(0);
	}
	rawSystem->locateGameRootFiles();

	switch (Game::title)
	{
	case Game::Type::Base:
		Log::note();
		Log::note("Setting scope to Base Game", Log::DEBUG);
		break;
	case Game::Type::Expansion:
		Log::note();
		Log::note("Setting scope to Expansion", Log::DEBUG);
		break;
	case Game::Type::Undefined:
		Log::note();
		Log::note("Setting scope to MEMLEAK_0x8523 - INVOKING BSOD STOP 0A", Log::DEBUG);
		break;
	}

	StartupLoader bootLoader;
	Log::note();
	Log::note("Loading MIX files:", Log::DEBUG);
	bootLoader.initiateMIX();

	if (MIXManager::getManager()->get("RA2MD.MIX") == nullptr && MIXManager::getManager()->get("RA2.MIX") == nullptr)
	{
		Log::note("Invalid directory set, terminating now...", Log::DEBUG);
		Log::close();
		system("pause");
		exit(0);
	}

	Log::note();
	Log::note("Loading INI files:", Log::DEBUG);
	Log::timerStart();
	bootLoader.initiateINI();
	Log::note();
	Log::note("Loading CSF files:", Log::DEBUG);
	bootLoader.initiateCSF();
	Log::note();

	ParamCollection* paramCollection = new ParamCollection();
	std::cout << "ParamCollection: Possible leak! Move when going to the GUI!" << std::endl;
	ActionCollection::getInstance()->parse(paramCollection);
	EventCollection::getInstance()->parse(paramCollection);
	SActionCollection::getInstance()->parse(paramCollection);

	GameModeCollection::getInstance()->parse();
	TheaterCollection::getInstance()->initiate(INIManager::getManager()->get(Config::configName));
}

void initiateAMap()
{
	if (Config::mapName.empty())
	{
		std::string mapToLoad;
		std::cout << "\nPlease enter the name of the map you want to load:" << std::endl;
		std::cin >> mapToLoad;
		Config::mapName = std::move(mapToLoad);
		std::cout << std::endl;
	}

	if (!MIXManager::getManager()->extract(Config::mapName))
	{
		Log::note("Map to load does not exist, unable to continue what so ever!");
		Log::close();
		system("pause");
		exit(0);
	}
}

void loadMap()
{
	Log::openOutput();
	std::wstring info = L"Game: " + CSFManager::getManager()->getValue("GUI:Version") + L" : " + FileSystem::getFileSystem()->getFileVersion(Config::executable);
	size_t found = info.find_first_of(L"\n");
	if (found != std::wstring::npos)
		info.erase(found, found + 1);
	Log::line("--- Game information ---", Log::INFO);
	Log::line(info, Log::EXTRAS);

	if (Config::hasAres)
	{
		INIFile* uimd = INIManager::getManager()->get(Config::UI);
		INISection* info = uimd->getSection("VersionInfo");
		if (info)
		{
			Log::line("--- Additional Ares Debug information ---", Log::INFO);
			Log::line("Name: " + info->getValue("Name"), Log::EXTRAS);
			Log::line("Version: " + info->getValue("Version"), Log::EXTRAS);
		}
	}

	MapLoader mapLoader;
	MapAssetLoader mapAssetLoader;
	INIFile* map = INIManager::getManager()->get(Config::mapName);	//Test for overwriting previous content (GAPOWRA-F for Soviet MD 01)
	Basic::getBasic()->parse();
	INIFile* mode = nullptr;
	if (mapLoader.locateGameMode(map))
	{
		mode = INIManager::getManager()->get(GameModeCollection::getInstance()->getCurrent()->fileName);
	}

	INIFile* rules = INIManager::getManager()->get(Config::rules);

	Log::line("---- Map information ----", Log::INFO);
	Log::line("Scenario name: " + Config::mapName, Log::EXTRAS);
	Log::line("Map name: " + Basic::getBasic()->name, Log::EXTRAS);
	if (!Basic::getBasic()->player.empty())
	{
		Log::line("This is a singleplayer map.", Log::EXTRAS);
		Config::isSP = true;
	}
	else
	{
		Log::line("This is a multiplayer map.", Log::EXTRAS);
		if (GameModeCollection::getInstance()->getCurrent())
			Log::line(L"Gamemode: " + GameModeCollection::getInstance()->getCurrent()->WGUIName, Log::EXTRAS);
	}
	Log::line();

	Log::note("Serious shit now... Decoding IsoMapPack5!", Log::DEBUG);
	Log::timerStart();
	INISection* pack = map->getSection("IsoMapPack5");
	IsoMapPack isoPack(pack);
	isoPack.read();

	Log::note("Time to Base64 IsoMapPack5: " + Log::getTimerValue(), Log::DEBUG);

	//std::string Base64StrEn = Base64_encode((unsigned char*) Base64Str.c_str(), Base64Str.length());
	//Log::timerStart();

	/*
	Little side information:
	Tiberian Sun's Firestorm Expansion pack will load exactly like below
	Basically firestrm.ini is an INI file that is loaded between rules.ini and <some_map>.map,
	you can compare it with RA2's game mode INI files, they overwrite previous content and can also add new content
	Between the call with 'map' and 'rules' as argument, the INI file from Firestorm would be loaded
	*/
	Log::timerStart();
	mapLoader.load(rules);
	mapLoader.load(mode);
	mapLoader.load(map);
	mapLoader.loadAI();
	Log::note("Loading game's objects took: " + Log::getTimerValue(), Log::DEBUG);

	//Log::note("Going to load all objects now!", Log::DEBUG);
	Log::timerStart();
	mapAssetLoader.load(mode);
	mapAssetLoader.load(map);
	mapAssetLoader.loadOverlay(map);
	Log::note("Loading all objects from the map took: " + Log::getTimerValue(), Log::DEBUG);

	mapLoader.dumpLists();
	mapAssetLoader.dumpTypes();

}

void validateMap()
{

	Log::note();
	Log::note("Going to validate the map now!", Log::DEBUG);
	Log::timerStart();
	MainValidator mainValidator;
	Log::note("Validating map objects took: " + Log::getTimerValue(), Log::DEBUG);
}

/*
	Main function
	Config variables will be read from a settings file.
*/
int _tmain(int argc, _TCHAR* argv[])
{
	std::wstring pathW = argv[0];
	std::string pathS(pathW.begin(), pathW.end());
	//Remove the executable from the location-string (this is not FA2 lol)
	pathS.erase(pathS.find_last_of('\\'), pathS.length());
	Config::editorRoot = std::move(pathS);
	handleArguments(argc, argv);

	Log::openDebug();
	Log::note("Starting session at: " + Log::getFormalDateTime(), Log::DEBUG);

	initiateEditor();
	initiateAMap();
	loadMap();
	validateMap();

	Log::note();
	Log::note("Ending a succesful session, duration: " + Log::getSessionTime(), Log::DEBUG);
	std::cout << "\n------------------------------------------------------------" << std::endl;
	Log::close();
	system("pause");

	return 0;
}
