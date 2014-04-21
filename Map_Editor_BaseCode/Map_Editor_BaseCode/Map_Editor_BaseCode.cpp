// ConsoleApplication1.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <cstdlib>
#include <Windows.h>
#include <GL/gl.h>
#include <gl/freeglut.h>
#include "Editor.FileSystem/FileManager/FileSystem.hpp"
#include "Editor.FileSystem/FileManager/RawFileSystem.hpp"
#include "Editor.FileSystem/FileManager/Managers/MixManager.hpp"
#include "Editor.FileSystem/FileManager/Managers/INIManager.hpp"	
#include "Editor.FileSystem/FileManager/Managers/TMPManager.hpp"
#include "Editor.FileSystem/FileManager/Managers/PALManager.hpp"
#include "Editor.FileSystem/FileManager/Managers/SHPManager.hpp"
#include "Editor.FileSystem/FileManager/Managers/VXLManager.hpp"
#include "Editor.FileSystem/FileManager/FileSystem.hpp"
#include "Editor.FileSystem/SHPFile/SHPFile.hpp"
#include "Editor.FileSystem/ShpFile/ShpImage.hpp"
#include "Editor.Engine/Loading/StartupLoader.hpp"		
#include "Editor.Engine/Map/TheaterCollection.hpp"
#include "Editor.FileSystem/INIFile/INIFile.hpp"
#include "Editor.FileSystem\IniFile\INISection.hpp"
#include "Editor.Engine/Game/Theater.hpp"
#include "Editor.Engine/Map/TileSet.hpp"
#include "Editor.Engine\Loading\MapLoader.hpp"
#include "Config.hpp"
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include "Log.hpp"

void displayMe(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(1.0, 5.0, 1.0);
	glVertex3f(0.5, 0.5, -2.0);
	glVertex3f(0.0, 0.5, 0.0);
	glEnd();
	glFlush();
}

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

	Log::open();
	Log::note("Starting session at: " + Log::getFormalDateTime(), Log::DEBUG);

	//TODO: Rename ambiguous functions
	RawFileSystem rawSystem;
	MIXManager::getManager()->assignRawSystem(&rawSystem);
	FileSystem::getFileSystem()->assignPointers(&rawSystem);
	Config::parse();
	rawSystem.locateGameRootFiles();

	StartupLoader bootLoader;
	Log::note();
	Log::note("Loading MIX files:", Log::DEBUG);
	bootLoader.initiateMIX();
	Log::note();
	Log::note("Loading INI files:", Log::DEBUG);
	bootLoader.initiateINI();

	//glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE);
	//glutInitWindowSize(300, 300);
	//glutInitWindowPosition(100, 100);
	//glutCreateWindow("Hello world :D");
	//glutDisplayFunc(displayMe);
	//glutMainLoop();

	TheaterCollection::getInstance()->initiate(INIManager::getManager()->get("CONFIG"));
	TheaterCollection::getInstance()->setCurrent("NEWURBAN");

	INIFile* urbann = INIManager::getManager()->get("urbannmd.ini");
	INIFile* temperat = INIManager::getManager()->get("temperatmd.ini");
	INIFile* rules = INIManager::getManager()->get("rulesmd.ini");
	INIFile* art = INIManager::getManager()->get("artmd.ini");

	INISection* overlay = rules->getSection("OverlayTypes");
	MapLoader mapLoader;

	mapLoader.allocateMainRules(rules, art);
	mapLoader.loadAll(rules, art);

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
	std::cout << "\n------------------------------------------------------------\nPress Enter to finish." << std::endl;
	Log::close();
	std::cin.get();

	return 0;
}



