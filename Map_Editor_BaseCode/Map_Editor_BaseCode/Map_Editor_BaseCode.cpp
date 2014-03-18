// ConsoleApplication1.cpp : Defines the entry point for the console application.
// Map_Editor_BaseCode.exe >> processLog.txt
// Use command above in DEBUG -> Map_Editor_BaseCode Properties... -> Debugging -> Command Arguments

#include "stdafx.h"
#include "Editor.FileSystem/FileManager/FileSystem.hpp"
#include "Editor.FileSystem/FileManager/RawFileSystem.hpp"
#include "Editor.FileSystem/FileManager/Managers/MixManager.hpp"
#include "Editor.FileSystem/FileManager/Managers/INIManager.hpp"	
#include "Editor.FileSystem/FileManager/Managers/TMPManager.hpp"
#include "Editor.FileSystem/FileManager/Managers/PALManager.hpp"
#include "Editor.FileSystem/FileManager/Managers/SHPManager.hpp"
#include "Editor.FileSystem/FileManager/Managers/VXLManager.hpp"
#include "Editor.FileSystem/FileManager/FileSystem.hpp"
#include "Editor.FileSystem/VoxelFile/VPLFile.hpp"
#include "Editor.Engine/Loading/StartupLoader.hpp"		
#include "Editor.Engine/Map/TheaterCollection.hpp"
#include "Editor.FileSystem/INIFile/INIFile.hpp"
#include "GlobalData.hpp"
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

/*
	Main function
	Mainly has debug and test code to verify MIX reading.
	GlobalData variables will be read from a settings file lateron.

	CURRENT LOADING TIME FOR INIS AND MIXES IS 04.89 seconds!
*/
int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Please make sure you have a proper location pointing to the file 'CONFIG' as it is very important!" << std::endl
		<< "It holds all important settings and is therefore critical to be loaded!" << std::endl;

	//TODO: Rename ambiguous functions
	RawFileSystem rawSystem;
	MIXManager mixManager(&rawSystem);
	FileSystem::getFileSystem()->assignPointers(&rawSystem, &mixManager);
	INIManager iniManager;
	TMPManager tmpManager;
	PALManager palManager;
	SHPManager shpManager;
	VXLManager vxlManager;
	rawSystem.locateGameRootFiles();

	StartupLoader bootLoader(&mixManager, &iniManager);
	std::cout << "========================= MIX =========================" << std::endl;
	bootLoader.initiateMIX();
	std::cout << "========================= INI =========================" << std::endl;
	bootLoader.initiateINI();

	//std::string name = "CNOILD.SHP";
	//shpManager.cache(name);

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
	
	std::cout << "\n------------------------------------------------------------\nPress Enter to finish." << std::endl;
	//std::cin.get();
	return 0;
}



