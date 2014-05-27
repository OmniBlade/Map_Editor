// ConsoleApplication1.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Editor.FileSystem/FileManager/FileSystem.hpp"
#include "Editor.FileSystem/FileManager/RawFileSystem.hpp"
#include "Editor.FileSystem/FileManager/Managers/INIManager.hpp"	
#include "Editor.FileSystem/FileManager/Managers/MIXmanager.hpp"	
#include "Editor.FileSystem/FileManager/FileSystem.hpp"
#include "Editor.Engine/Loading/StartupLoader.hpp"		
#include "Editor.Engine/Map/TheaterCollection.hpp"
#include "Editor.FileSystem/INIFile/INIFile.hpp"
#include "Editor.FileSystem/IniFile/INISection.hpp"
#include "Editor.Engine/Loading/MapLoader.hpp"
#include "Editor.Configuration/ConfigLoader.hpp"
#include "Editor.Engine\Game\GameModeCollection.hpp"
#include "Config.hpp"
#include "Arguments.hpp"
#include "Log.hpp"
#include <cstdlib>
#include <Windows.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

/*
	Main function
	Config variables will be read from a settings file.
*/
int _tmain(int argc, _TCHAR* argv[])
{
	std::wstring pathW = argv[0];
	std::string pathS(pathW.begin(), pathW.end());
	//Remove the executable
	pathS.erase(pathS.find_last_of('\\'), pathS.length());
	Config::editorRoot = pathS;
	handleArguments(argc, argv);

	Log::open();
	Log::note("Starting session at: " + Log::getFormalDateTime(), Log::DEBUG);

	//TODO: Rename ambiguous functions
	RawFileSystem rawSystem;
	MIXManager::getManager()->assign(&rawSystem);
	FileSystem::getFileSystem()->assign(&rawSystem);

	ConfigLoader configLoader;
	if (!configLoader.chooseConfig())
	{
		Log::close();
		std::cin.get();
		return 0;
	}

	if (Config::installDir.empty())
	{
		Log::note("Unable to determine install directory, terminating now...", Log::DEBUG);
		Log::close();
		std::cin.get();
		return 0;
	}
	rawSystem.locateGameRootFiles();

	StartupLoader bootLoader;
	Log::note();
	Log::note("Loading MIX files:", Log::DEBUG);
	bootLoader.initiateMIX();
	Log::note();
	Log::note("Loading INI files:", Log::DEBUG);
	Log::timerStart();
	bootLoader.initiateINI();
	Log::note();
	Log::note("Loading CSF files:", Log::DEBUG);
	bootLoader.initiateCSF();

 	GameModeCollection::getInstance()->parse();
	TheaterCollection::getInstance()->initiate(INIManager::getManager()->get(Config::configName));

	std::string mapToLoad;

	if (Config::mapName.empty())
	{
		std::cout << "\nPlease enter the name of the map you want to load:" << std::endl;
		std::cin >> mapToLoad;
		std::cout << std::endl;
	}
	else
	{
		mapToLoad = Config::mapName;
	}

	MIXManager::getManager()->extract(mapToLoad);

	MapLoader mapLoader;
	INIFile* map = INIManager::getManager()->get(mapToLoad);	//Test for overwriting previous content (GAPOWRA-F for Soviet MD 01)
	INIFile* mode = nullptr;
	if (mapLoader.locateGameMode(map))
	{
		mode = INIManager::getManager()->get(GameModeCollection::getInstance()->getCurrent()->fileName);
	}

	INIFile* rules = INIManager::getManager()->get(Config::rules);


	//Log::timerStart();

	/*
		Little side information:
		Tiberian Sun's Firestorm expansion pack will load exactly like below
		Basically firestrm.ini is an INI file that is loaded between rules.ini and <some_map>.map,
		you can compare it with RA2's game mode INI files, they overwrite previous content and can also add new content
		Between the call with 'map' and 'rules' as argument, the INI file from Firestorm would be loaded
	*/
	Log::timerStart();
	mapLoader.load(rules);
	mapLoader.load(mode);
	mapLoader.load(map);

	Log::note("Loading everything took: " + Log::getTimerValue(), Log::DEBUG);
	mapLoader.dumpLists();
	
	Log::note();
	Log::note("Ending a succesful session, duration: " + Log::getSessionTime(), Log::DEBUG);
	std::cout << "\n------------------------------------------------------------" << std::endl;
	Log::close();
	system("pause");

	return 0;
}
