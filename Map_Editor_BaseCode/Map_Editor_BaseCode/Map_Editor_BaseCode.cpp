// ConsoleApplication1.cpp : Defines the entry point for the console application.
// Map_Editor_BaseCode.exe >> processLog.txt
// Use command above in DEBUG -> Map_Editor_BaseCode Properties... -> Debugging -> Command Arguments

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
#include "GlobalData.hpp"
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

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
Mainly has debug and test code to verify MIX reading.
GlobalData variables will be read from a settings file lateron.

CURRENT LOADING TIME FOR INIS AND MIXES IS 04.89 seconds!
*/
int _tmain(int argc, char* argv[])
{
	std::cout << "Please make sure you have a proper location pointing to the file 'CONFIG' as it is very important!" << std::endl
		<< "It holds all important settings and is therefore critical to be loaded!" << std::endl;

	//TODO: Rename ambiguous functions
	RawFileSystem rawSystem;
	MIXManager::getManager()->assignRawSystem(&rawSystem);
	FileSystem::getFileSystem()->assignPointers(&rawSystem);
	INIManager::getManager()->parseConfigFile("CONFIG");
	rawSystem.locateGameRootFiles();

	StartupLoader bootLoader;
	std::cout << "========================= MIX =========================" << std::endl;
	bootLoader.initiateMIX();
	std::cout << "========================= INI =========================" << std::endl;
	bootLoader.initiateINI();

	//glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE);
	//glutInitWindowSize(300, 300);
	//glutInitWindowPosition(100, 100);
	//glutCreateWindow("Hello world :D");
	//glutDisplayFunc(displayMe);
	//glutMainLoop();

	INIFile* temperat = INIManager::getManager()->get("TEMPERAT.INI");
	Theater derp(temperat);
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
	
	std::cout << "\n------------------------------------------------------------\nPress Enter to finish." << std::endl;
	//std::cin.get();
	return 0;
}



