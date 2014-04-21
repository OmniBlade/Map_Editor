#pragma once

#include <string>
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"

class AI
{
public:
	AI();
	
	void loadRules(INIFile* file);

	std::string BuildConst = "";
	std::string BuildPower = "";
	std::string BuildRefinery = "";
	std::string BuildBarracks = "";
	std::string BuildTech = "";
	std::string BuildWeapons = "";
	std::string AlliedBaseDefenses = "";
	std::string SovietBaseDefenses = "";
	std::string ThirdBaseDefenses = "";
	std::string BuildDefense = "";
	std::string BuildPDefense = "";
	std::string BuildAA = "";
	std::string BuildHelipad = "";
	std::string BuildRadar = "";
	std::string ConcreteWalls = "";
	std::string NSGates = "";
	std::string EWGates = "";
	std::string BuildNavalYard = "";
	std::string BuildDummy = "";
	std::string NeutralTechBuildings = "";
};

