#pragma once

#include "../../Editor.FileSystem/IniFile/INIFile.hpp"

class IQ
{
public:
	IQ();

	void loadRules(INIFile* file);

	int MaxIQLevels = 5;
	int SuperWeapons;
	int Production;
	int GuardArea;
	int RepairSell;
	int AutoCrush;
	int Scatter;
	int ContentScan;
	int Aircraft;
	int Harvester;
	int SellBack;
};

/*
MaxIQLevels=5
SuperWeapons=4
Production=5
GuardArea=2
RepairSell=1
AutoCrush=2
Scatter=2
ContentScan=3
Aircraft=3
Harvester=2
SellBack=2
*/