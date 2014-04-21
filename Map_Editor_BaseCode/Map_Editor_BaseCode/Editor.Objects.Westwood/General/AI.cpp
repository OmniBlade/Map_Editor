#include "stdafx.h"
#include "AI.hpp"
#include "EntryHelper.hpp"
#include "../Types/BuildingType.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"

AI::AI()
{
}

void AI::loadRules(INIFile* file)
{
	INISection* section = file->getSection("AI");
	if (!section) return;

	allocateList(BuildingType::Array, section->readStringValue("BuildConst", BuildConst));
	allocateList(BuildingType::Array, section->readStringValue("BuildPower", BuildPower));
	allocateList(BuildingType::Array, section->readStringValue("BuildRefinery", BuildRefinery));
	allocateList(BuildingType::Array, section->readStringValue("BuildBarracks", BuildBarracks));
	allocateList(BuildingType::Array, section->readStringValue("BuildTech", BuildTech));
	allocateList(BuildingType::Array, section->readStringValue("BuildWeapons", BuildWeapons));
	allocateList(BuildingType::Array, section->readStringValue("AlliedBaseDefenses", AlliedBaseDefenses));
	allocateList(BuildingType::Array, section->readStringValue("SovietBaseDefenses", SovietBaseDefenses));
	allocateList(BuildingType::Array, section->readStringValue("ThirdBaseDefenses", ThirdBaseDefenses));
	allocateList(BuildingType::Array, section->readStringValue("BuildDefense", BuildDefense));
	allocateList(BuildingType::Array, section->readStringValue("BuildPDefense", BuildPDefense));
	allocateList(BuildingType::Array, section->readStringValue("BuildAA", BuildAA));
	allocateList(BuildingType::Array, section->readStringValue("BuildHelipad", BuildHelipad));
	allocateList(BuildingType::Array, section->readStringValue("BuildRadar", BuildRadar));
	allocateList(BuildingType::Array, section->readStringValue("ConcreteWalls", ConcreteWalls));
	allocateList(BuildingType::Array, section->readStringValue("NSGates", NSGates));
	allocateList(BuildingType::Array, section->readStringValue("EWGates", EWGates));
	allocateList(BuildingType::Array, section->readStringValue("BuildNavalYard", BuildNavalYard));
	allocateList(BuildingType::Array, section->readStringValue("BuildDummy", BuildDummy));
	allocateList(BuildingType::Array, section->readStringValue("NeutralTechBuildings", NeutralTechBuildings));

}