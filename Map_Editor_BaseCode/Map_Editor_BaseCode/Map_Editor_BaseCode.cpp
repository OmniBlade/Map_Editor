// ConsoleApplication1.cpp : Defines the entry point for the console application.
// Map_Editor_BaseCode.exe >> processLog.txt
// Use command above in DEBUG -> Map_Editor_BaseCode Properties... -> Debugging -> Command Arguments

#include "stdafx.h"
#include "Handlers/MixFileHandler.hpp"
#include "Handlers/INIFileHandler.hpp"
#include "Loading/StartupLoader.hpp"
#include "FileSystem/PaletteFile/PaletteFile.hpp"
#include "FileSystem/INIFile/INIFile.hpp"
#include "GlobalData.hpp"
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
	//GlobalData::MAIN_InstallDir = "D:\\Westwood\\RA2 - kopie";
	//GlobalData::MAIN_BackSlash = "\\";
	//GlobalData::MAIN_MissionDisk = "MD";
	//GlobalData::MAIN_Expand = "EXPAND";
	//GlobalData::MAIN_Ecache = "ECACHE";
	//GlobalData::MAIN_Elocal = "ELOCAL";

	std::cout << "Please make sure you have a proper location pointing to the file 'CONFIG' as it is very important!" << std::endl
		<< "It holds all important settings and is therefore critical to be loaded, in code, edit a few lines below this line!" << std::endl;

	MixFileHandler mixHandler;
	INIFileHandler iniHandler;

	std::string directory = "D:\\Map_Editor_GIT\\Map_Editor\\Map_Editor_BaseCode\\Debug";
	iniHandler.parseConfigFile(directory);	//Sorry, this has to be done before the shit gets real. Done only once though

	StartupLoader startupLoader(&mixHandler, &iniHandler);
	startupLoader.initiateMIX();
	startupLoader.initiateINI();

	
	std::cout << "\n\nPress Enter to finish." << std::endl;
	std::cin.get();
	return 0;
}



