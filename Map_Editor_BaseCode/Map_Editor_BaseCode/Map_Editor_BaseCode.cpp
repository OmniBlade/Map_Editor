// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Handlers/MixFileHandler.hpp"
#include "Loading/StartupLoader.hpp"
#include "GlobalData.hpp"
#include <iostream>
#include <vector>
#include <string>

int _tmain(int argc, _TCHAR* argv[])
{
	GlobalData::installDir = "D:\\Westwood\\RA2 - kopie";
	GlobalData::backSlash = "\\";
	GlobalData::missionDisk = "MD";

	MixFileHandler mixHandler;
	StartupLoader startupLoader(&mixHandler);
	startupLoader.initiateMIX();
	mixHandler.dumpMIXNames();

	std::cout << "Trying to dump rulesmo.ini!" << std::endl;
	mixHandler.extractFileFromMix("des.mix");
	std::cout << "Trying to dump tension.wav!" << std::endl;
	mixHandler.dumpMIXNames();
	mixHandler.extractFileFromMix("rough02.tem");
	std::cout << "Trying to dump keyboardmd.ini!" << std::endl;
	mixHandler.extractFileFromMix("keyboardmd.ini");
	//D:\\HAN\\Semester_1\\Eclipse_Workspace2\\Map_Editor\\Debug\\textmix_2file.mix
	//D:\\Dropbox\\FinalOmega - BETA\\marble.mix
	//D:\\Westwood\\RA2 - kopie
	//D:\Dropbox\Mental Omega LC 9.0

	std::cin.get();
	return 0;
}

