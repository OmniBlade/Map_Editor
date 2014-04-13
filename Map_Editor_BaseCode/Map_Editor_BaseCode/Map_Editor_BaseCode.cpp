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
#include "Editor.Engine/Map/Theater.hpp"
#include "Editor.Engine/Map/TileSet.hpp"
#include "Editor.Objects.Westwood/Types/OverlayType.hpp"
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
	Log::line("Please make sure your CONFIG file is in the root of the executable!", Log::WARNING);
	Log::line("Starting session at: " + Log::getFormalDateTime(), Log::DEBUG);

	//TODO: Rename ambiguous functions
	RawFileSystem rawSystem;
	MIXManager::getManager()->assignRawSystem(&rawSystem);
	FileSystem::getFileSystem()->assignPointers(&rawSystem);
	Config::parse();
	rawSystem.locateGameRootFiles();

	StartupLoader bootLoader;
	Log::line("", Log::D_EMPTY);
	Log::line("Loading MIX files:", Log::DEBUG);
	bootLoader.initiateMIX();
	Log::line("", Log::D_EMPTY);
	Log::line("Loading INI files:", Log::DEBUG);
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

	INIFile* temperat = INIManager::getManager()->get("urbannmd.ini");
	INIFile* rules = INIManager::getManager()->get("rulesmd.ini");
	INIFile* art = INIManager::getManager()->get("artmd.ini");
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
	
	Log::line("", Log::EMPTY);
	Log::line("", Log::D_EMPTY);
	Log::line("Ending a succesful session, duration: " + Log::getSessionTime() , Log::DEBUG);
	Log::line("Total session time is: " + Log::getSessionTime(), Log::INFO);
	Log::line("Shutting down, thank you.", Log::INFO);
	std::cout << "\n------------------------------------------------------------\nPress Enter to finish." << std::endl;
	Log::close();
	std::cin.get();

	return 0;
}



