// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Handlers/MixFileHandler.hpp"
#include "Handlers/INIFileHandler.hpp"
#include "Loading/StartupLoader.hpp"
#include "GlobalData.hpp"
#include <iostream>
#include <vector>
#include <string>

/*
	Main function
	Mainly has debug and test code to verify MIX reading.
	GlobalData variables will be read from a settings file lateron.
*/
int _tmain(int argc, _TCHAR* argv[])
{
	GlobalData::installDir = "D:\\Westwood\\RA2 - kopie";
	GlobalData::backSlash = "\\";
	GlobalData::missionDisk = "MD";
	GlobalData::expand = "EXPAND";
	GlobalData::ecache = "ECACHE";
	GlobalData::elocal = "ELOCAL";

	MixFileHandler mixHandler;
	INIFileHandler iniHandler;
	StartupLoader startupLoader(&mixHandler);
	startupLoader.initiateMIX();
	startupLoader.initiateINI();

	std::cin.get();
	return 0;
}

