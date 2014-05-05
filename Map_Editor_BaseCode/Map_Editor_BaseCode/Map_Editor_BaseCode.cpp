// ConsoleApplication1.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <cstdlib>
#include <Windows.h>
#include "Editor.FileSystem/FileManager/FileSystem.hpp"
#include "Editor.FileSystem/FileManager/RawFileSystem.hpp"
#include "Editor.FileSystem/FileManager/Managers/MixManager.hpp"
#include "Editor.FileSystem/FileManager/Managers/INIManager.hpp"	
#include "Editor.FileSystem/FileManager/Managers/TMPManager.hpp"
#include "Editor.FileSystem/FileManager/Managers/PALManager.hpp"
#include "Editor.FileSystem/FileManager/Managers/SHPManager.hpp"
#include "Editor.FileSystem/FileManager/Managers/VXLManager.hpp"
#include "Editor.FileSystem\FileManager\Managers\CSFManager.hpp"
#include "Editor.FileSystem/FileManager/FileSystem.hpp"
#include "Editor.FileSystem/SHPFile/SHPFile.hpp"
#include "Editor.FileSystem/ShpFile/ShpImage.hpp"
#include "Editor.Engine/Loading/StartupLoader.hpp"		
#include "Editor.Engine/Map/TheaterCollection.hpp"
#include "Editor.FileSystem/INIFile/INIFile.hpp"
#include "Editor.FileSystem\IniFile\INISection.hpp"
#include "Editor.FileSystem\CsfFile\CSFFile.hpp"
#include "Editor.Engine/Game/Theater.hpp"
#include "Editor.Engine/Map/TileSet.hpp"
#include "Editor.Engine\Loading\MapLoader.hpp"
#include "Editor.Configuration\ConfigLoader.hpp"
#include "Config.hpp"
#include "Arguments.hpp"
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include "Log.hpp"

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
	MIXManager::getManager()->assignRawSystem(&rawSystem);
	FileSystem::getFileSystem()->assignPointers(&rawSystem);

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
	bootLoader.initiateINI();
	Log::note();
	Log::note("Loading CSF files:", Log::DEBUG);
	bootLoader.initiateCSF();

	TheaterCollection::getInstance()->initiate(INIManager::getManager()->get(Config::configName));
	TheaterCollection::getInstance()->setCurrent("NEWURBAN");		//Test code to check Tileset loading for NEWURBAN

	INIFile* rules = INIManager::getManager()->get(Config::rules);
	ShpFile* shp = SHPManager::getManager()->get("dipshit.SHP");	//Test for missing items
	INIFile* map = INIManager::getManager()->get("sov01umd.map");	//Test for overwriting previous content (GAPOWRA-F for Soviet MD 01)
	MapLoader mapLoader;

	Log::timerStart();

	/*
		Little side information:
		Tiberian Sun's Firestorm expansion pack will load exactly like below
		Basically firestrm.ini is an INI file that is loaded between rules.ini and <some_map>.map,
		you can compare it with RA2's game mode INI files, they overwrite previous content and can also add new content
		Between the call with 'map' and 'rules' as argument, the INI file from Firestorm would be loaded
	*/
	mapLoader.allocateMainRules(rules);
	mapLoader.loadAll(rules);
	mapLoader.allocateMainRules(map);
	mapLoader.loadAll(map);

	Log::note("Parsing all ObjectTypes from rules and map took: " + Log::getTimerValue(), Log::DEBUG);
	mapLoader.dumpLists();

	//Theater derp(temperat);

	//std::string tileset = "TileSet0014";
	//TileSet set0010(10, temperat->getSection(tileset));

	//mixManager.cache("RA2.MIX");
	//mixManager.cache("LOCAL.MIX");
	//vxlManager.cacheVPL("VOXELS.VPL");

	//VPLFile::getVPL()->read();
//	INIFileHandler iniHandler;

//	std::string directory = "D:\\Map_Editor_GIT\\Map_Editor\\Map_Editor_BaseCode\\Debug";
//	iniHandler.parseConfigFile(directory);	//Sorry, this has to be done before the shit gets real. Done only once though

//	TheaterCollection theaters(iniHandler.getAnINIFile("CONFIG"));


	//std::string tmpName = "droadj11.tem";
	//TMPFile tmpFile(tmpName);

	//StartupLoader startupLoader(&mixHandler, &iniHandler);
	//startupLoader.initiateMIX();
	//startupLoader.initiateINI();

	//std::string mapfile = "all01t.map";
	//iniHandler.createVirtualINI(mapfile);
	
	Log::note();
	Log::note("Ending a succesful session, duration: " + Log::getSessionTime(), Log::DEBUG);
	std::cout << "\n------------------------------------------------------------" << std::endl;
	Log::close();
	system("pause");

	return 0;
}



