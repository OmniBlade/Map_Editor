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
#include "Editor.Engine\Basics\Lighting.hpp"
#include "Editor.Engine\Basics\SpecialFlag.hpp"
#include "Editor.Engine\Basics\MapStats.hpp"
#include "Editor.FileSystem\MapFile\MapMods.h"
#include "Editor.FileSystem\MapFile\ParamCollection.hpp"
#include "Editor.FileSystem\MapFile\SActionCollection.hpp"
#include "Editor.FileSystem\MapFile\ActionCollection.hpp"
#include "Editor.FileSystem\MapFile\EventCollection.hpp"
#include "Editor.Engine\Map\IsoMapPack.hpp"
#include "Editor.Engine\Map\OverlayPack.hpp"
#include "Editor.Engine\Map\PreviewPack.h"
#include "Editor.FileSystem\FileManager\Managers\EncManager.hpp"
#include "Editor.FileSystem\EncFile\EncFile.hpp"
#include "Config.hpp"
#include "Arguments.hpp"
#include "Log.hpp"
#include <cstdlib>
#include <Windows.h>
#include <sstream>
#include <iostream>
#include <memory>
#include <vector>
#include <string>

//These are mainly testing includes
#include "Editor.Engine\Lists\ListProvider.h"
#include "Editor.Engine\Types\SpecialOverlays.h"
#include "Editor.Objects.Westwood\OverlayTypeValidator.h"
#include "Editor.FileSystem\MapFile\MapWriter.h"

ParamCollection* paramCollection;
MainValidator* mainValidator;

void initiateEditor()
{
	//TODO: Rename ambiguous functions
	RawFileSystem* rawSystem = new RawFileSystem();;
	MIXManager::instance()->assign(rawSystem);
	FileSystem::getFileSystem()->assign(rawSystem);

	ConfigLoader configLoader;

	if (!configLoader.chooseConfig())
	{
		Log::close();
		system("pause");
		exit(0);
	}

	if (Config::installDir.empty())
	{
		Log::line("Unable to determine install directory, terminating now...", Log::DEBUG);
		Log::close();
		system("pause");
		exit(0);
	}
	rawSystem->locateGameRootFiles();

	switch (Game::title)
	{
	case Game::Type::Base:
		Log::line();
		Log::line("Setting scope to Base Game", Log::DEBUG);
		break;
	case Game::Type::Expansion:
		Log::line();
		Log::line("Setting scope to Expansion", Log::DEBUG);
		break;
	case Game::Type::Undefined:
		Log::line();
		Log::line("Undefined game detected! Unable to set scope.", Log::DEBUG);
		break;
	}

	StartupLoader bootLoader;
	Log::line();
	Log::line("Loading MIX files:", Log::DEBUG);
	bootLoader.initiateMIX();

	if (MIXManager::instance()->get("RA2MD.MIX") == nullptr && MIXManager::instance()->get("RA2.MIX") == nullptr)
	{
		Log::line("Invalid directory set, terminating now...", Log::DEBUG);
		Log::close();
		system("pause");
		exit(0);
	}

	Log::line();
	Log::line("Loading INI files:", Log::DEBUG);
	Log::timerStart(); //To measure the INI loading time!
	bootLoader.initiateINI();
	Log::line();
	Log::line("Loading CSF files:", Log::DEBUG);
	bootLoader.initiateCSF();

	if (!bootLoader.validateEssentialFiles())
	{
		Log::line("At least one core editor file did not make it through validation, terminating now...", Log::DEBUG);
		//Log::close();
		//system("pause");
		//exit(0);
	}

	std::cout << "ParamCollection: Possible leak! Move when going to the GUI!" << std::endl;
	paramCollection = new ParamCollection();
	ActionCollection::getInstance()->parse(paramCollection);
	EventCollection::getInstance()->parse(paramCollection);
	SActionCollection::getInstance()->parse(paramCollection);

	GameModeCollection::getInstance()->parse();
	TheaterCollection::getInstance()->initiate(INIManager::instance()->get(Config::configName));
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

	if (!MIXManager::instance()->extract(Config::mapName))
	{
		Log::line("Map to load does not exist, unable to continue what so ever!");
		Log::close();
		system("pause");
		exit(0);
	}
}

void loadMap()
{
	Log::timerStart();
	Log::openOutput(); // Can't move, requires map INI name in file's name!	
	std::wstring info = L"Game: " + CSFManager::instance()->getValue("GUI:Version") + L" : " + FileSystem::getFileSystem()->getFileVersion(Config::executable);
	size_t found = info.find_first_of(L"\n");
	if (found != std::wstring::npos)
		info.erase(found, found + 1);
	Log::validatorLine("--- Game information ---", Log::INFO);
	Log::validatorLine(info, Log::EXTRAS);

	if (Config::hasAres)
	{
		INIFile* uimd = INIManager::instance()->get(Config::UI);
		INISection* info = uimd->getSection("VersionInfo");
		if (info)
		{
			Log::validatorLine("--- Additional Ares Debug information ---", Log::INFO);
			Log::validatorLine("Name: " + info->getValue("Name"), Log::EXTRAS);
			Log::validatorLine("Version: " + info->getValue("Version"), Log::EXTRAS);
		}
	}

	MapLoader mapLoader;
	MapAssetLoader mapAssetLoader;
	INIFile* map = INIManager::instance()->get(Config::mapName);	//Test for overwriting previous content (GAPOWRA-F for Soviet MD 01)
	Basic::getBasic()->parse();
	INIFile* mode = nullptr;
	if (mapLoader.locateGameMode(map))
	{
		mode = INIManager::instance()->get(GameModeCollection::getInstance()->getCurrent()->fileName);
	}

	INIFile* rules = INIManager::instance()->get(Config::rules);

	Log::validatorLine("---- Map information ----", Log::INFO);
	Log::validatorLine("Scenario name: " + Config::mapName, Log::EXTRAS);
	Log::validatorLine("Map name: " + Basic::getBasic()->Name, Log::EXTRAS);
	if (!Basic::getBasic()->Player.empty())
	{
		Log::validatorLine("This is a singleplayer map.", Log::EXTRAS);
		Config::isSP = true;
	}
	else
	{
		Log::validatorLine("This is a multiplayer map.", Log::EXTRAS);
		if (GameModeCollection::getInstance()->getCurrent())
			Log::validatorLine(L"Gamemode: " + GameModeCollection::getInstance()->getCurrent()->WGUIName, Log::EXTRAS);
	}
	Log::validatorLine();

	INISection* pack = map->getSection("IsoMapPack5");
	IsoMapPack* isoPack = new IsoMapPack(pack);
	isoPack->read();

	OverlayPack* opack = new OverlayPack(map);
	opack->read();

	PreviewPack* pPack = new PreviewPack(map);
	pPack->read();

	/*
		Little side information:
		Tiberian Sun's Firestorm Expansion pack will load exactly like below
		Basically firestrm.ini is an INI file that is loaded between rules.ini and <some_map>.map,
		you can compare it with RA2's game mode INI files, they overwrite previous content and can also add new content
		Between the call with 'map' and 'rules' as argument, the INI file from Firestorm would be loaded
	*/
	//Log::timerStart();
	mapLoader.load(rules, "Rules");
	mapLoader.load(mode, "Gamemode");
	mapLoader.setGlobalCountries();
	mapLoader.load(map, "Map");
	mapLoader.loadGlobalVariable(); // Causes crash on exit when profiled as WWType
	mapLoader.loadAI();

	OverlayTypeValidator otv;

	//Log::line("Going to load all objects now!", Log::DEBUG);

	MapStats::instance()->parse();
	Basic::getBasic()->parse();
	SpecialFlag::instance()->parse();
	Lighting::instance()->parse();
	mapAssetLoader.load(mode, "Gamemode");
	mapAssetLoader.setGlobalValues();
	mapAssetLoader.load(map, "Map");

	opack->createOverlayFromData();

	MapMods* mods = new MapMods();
	mods->parse(map);
	
	Basic::getBasic()->assignPointers(); //This is vital! Waypoints, Houses etc aren't known before mapAssetLoader

	Log::line("Loading all objects from the map took: " + Log::getTimerValue(), Log::DEBUG);

	mapLoader.dumpLists();
	mapAssetLoader.dumpTypes();
}

void validateMap()
{

	Log::line();
	Log::line("Going to validate the map now!", Log::DEBUG);
	Log::timerStart();
	mainValidator = new MainValidator(paramCollection);
	mainValidator->validateAll();
	Log::line("Validating map objects took: " + Log::getTimerValue(), Log::DEBUG);
}

#include "Editor.FileSystem\IniFile\DigestClass.h"

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
	Log::line("THIS IS AN UNSTABLE BUILD OF THE MAP EDITOR, BUGS ARE TO BE EXPECTED", Log::DEBUG);
	Log::line();
	Log::line("Starting session at: " + Log::getFormalDateTime(), Log::DEBUG);

	initiateEditor();
	initiateAMap();
	loadMap();
	validateMap();
	
	MapWriter writer;
	writer.writeMap("C:\\Users\\Rik\\Desktop\\map_write_test.map");

	Log::line();
	Log::line("Ending a succesful session, duration: " + Log::getSessionTime(), Log::DEBUG);
	std::cout << "\n------------------------------------------------------------" << std::endl;
	Log::close();
	system("pause");

	delete mainValidator;
	delete paramCollection;
	delete IsoMapPack::instance;
	delete OverlayPack::instance;
	delete PreviewPack::instance;

	return 0;
}
