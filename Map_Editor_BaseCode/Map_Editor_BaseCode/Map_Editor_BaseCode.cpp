// ConsoleApplication1.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Editor.FileSystem/FileManager/FileSystem.hpp"
#include "Editor.FileSystem/FileManager/RawFileSystem.hpp"
#include "Editor.FileSystem/FileManager/Managers/INIManager.hpp"	
#include "Editor.FileSystem/FileManager/Managers/MIXmanager.hpp"	
#include "Editor.FileSystem/FileManager/Managers/CSFManager.hpp"	
#include "Editor.FileSystem/FileManager/FileSystem.hpp"
#include "Editor.Engine/Loading/StartupLoader.hpp"		
#include "Editor.Engine/Map/Theater/TheaterCollection.hpp"
#include "Editor.FileSystem/INIFile/INIFile.hpp"
#include "Editor.FileSystem/IniFile/INISection.hpp"
#include "Editor.Engine/Loading/MapLoader.h"
#include "Editor.Engine\Loading\GenericLoader.h"
#include "Editor.Configuration/ConfigLoader.hpp"
#include "Editor.Engine\Game\GameModeCollection.hpp"
#include "Editor.Map.Validator\MainValidator.hpp"

#include "Editor.FileSystem\IniFile\DigestClass.h"
#include "Editor.FileSystem\MapFile\Triggers\ParamCollection.hpp"
#include "Editor.FileSystem\MapFile\Triggers\SActionCollection.hpp"
#include "Editor.FileSystem\MapFile\Triggers\ActionCollection.hpp"
#include "Editor.FileSystem\MapFile\Triggers\EventCollection.hpp"

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

std::unique_ptr<ParamCollection> paramCollection;
std::unique_ptr<MainValidator> mainValidator;
std::unique_ptr<INIFile> map;
std::unique_ptr<INIFile> mapOrigin;
std::unique_ptr<RawFileSystem> rawSystem;

std::string mapName = "TEST.MAP";

void initiateEditor()
{
	//TODO: Rename ambiguous functions
	rawSystem = std::make_unique<RawFileSystem>();
	MIXManager::instance()->assign(rawSystem.get());
	FileSystem::getFileSystem()->assign(rawSystem.get());

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

	if (MIXManager::instance()->get("RA2MD.MIX") == nullptr && MIXManager::instance()->get("RA2.MIX") == nullptr 
		&& MIXManager::instance()->get("TIBSUN.MIX") == nullptr)
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

	paramCollection = std::make_unique<ParamCollection>();
	ActionCollection::getInstance()->parse(paramCollection.get());
	EventCollection::getInstance()->parse(paramCollection.get());
	SActionCollection::getInstance()->parse(paramCollection.get());

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

	Log::openOutput(); // Can't move, requires map INI name in file's name!	
}

void loadGenericData()
{
	GenericLoader genLoader;
	genLoader.loadAudioVisual();
}

void loadMap()
{
	Log::line();
	Log::line();
	Log::line("SESSION - Loading map: " + Config::mapName, Log::DEBUG);
	map = std::make_unique<INIFile>(FileSystem::getFileSystem()->getFile(Config::mapName)); //Assuming the reader in props is always valid... :D
	MapLoader mapLoader(map.get(), true);
	mapLoader.load();
}

void reloadMap()
{
	Log::line();
	Log::line();
	Log::line("SESSION - Reloading map: " + Config::mapName, Log::DEBUG);
	MapLoader loader;
	loader.reload();
}

void validateMap()
{
	Log::line();
	Log::line("Going to validate the map now!", Log::DEBUG);
	Log::timerStart();
	mainValidator = std::make_unique<MainValidator>(paramCollection.get());
	mainValidator->validateAll();
	Log::line("Validating map objects took: " + Log::getTimerValue(), Log::DEBUG);
}

void setEditorRoot(const std::wstring& path)
{
	std::string pathS(path.begin(), path.end());
	//Remove the executable from the location-string (this is not FA2 lol)
	pathS.erase(pathS.find_last_of('\\'), pathS.length());
	Config::editorRoot = std::move(pathS);
}

/*
	Main function
	Config variables will be read from a settings file.
*/
int _tmain(int argc, _TCHAR* argv[])
{
	setEditorRoot(argv[0]);
	handleArguments(argc, argv);

	Log::openDebug();
	Log::line("THIS IS AN UNSTABLE BUILD OF THE MAP EDITOR, BUGS ARE TO BE EXPECTED", Log::DEBUG);
	Log::line();
	Log::line("Starting session at: " + Log::getFormalDateTime(), Log::DEBUG);

	initiateEditor();
	initiateAMap();
	loadMap();
	//validateMap();

	MapWriter writer;
	writer.setNamesFileName(mapName);
	writer.writeAll(Config::installDir + Config::backSlash + mapName);

	Config::mapName = "";

	initiateAMap();
	loadMap();
	MapWriter secondWriter;
	secondWriter.setNamesFileName("TEST3.MAP");
	secondWriter.writeAll(Config::installDir + Config::backSlash + "TEST3.MAP");

	Log::line();

	Log::line("Ending a succesful session, duration: " + Log::getSessionTime(), Log::DEBUG);
	std::cout << "\n------------------------------------------------------------" << std::endl;
	Log::close();
	system("pause");

	return 0;
}

/*std::wstring info = L"Game: " + CSFManager::instance()->getValue("GUI:Version") + L" : " + FileSystem::getFileSystem()->getFileVersion(Config::executable);
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
}*/

/*
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
*/