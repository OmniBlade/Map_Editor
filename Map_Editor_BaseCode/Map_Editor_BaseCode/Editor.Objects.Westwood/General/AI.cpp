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

	section->readStringValue("BuildConst", BuildConst);
	section->readStringValue("BuildPower", BuildPower);
	section->readStringValue("BuildRefinery", BuildRefinery);
	section->readStringValue("BuildBarracks", BuildBarracks);
	section->readStringValue("BuildTech", BuildTech);
	section->readStringValue("BuildWeapons", BuildWeapons);
	section->readStringValue("AlliedBaseDefenses", AlliedBaseDefenses);
	section->readStringValue("SovietBaseDefenses", SovietBaseDefenses);
	section->readStringValue("ThirdBaseDefenses", ThirdBaseDefenses);
	section->readStringValue("BuildDefense", BuildDefense);
	section->readStringValue("BuildPDefense", BuildPDefense);
	section->readStringValue("BuildAA", BuildAA);
	section->readStringValue("BuildHelipad", BuildHelipad);
	section->readStringValue("BuildRadar", BuildRadar);
	section->readStringValue("ConcreteWalls", ConcreteWalls);
	section->readStringValue("NSGates", NSGates);
	section->readStringValue("EWGates", EWGates);
	section->readStringValue("BuildNavalYard", BuildNavalYard);
	section->readStringValue("BuildDummy", BuildDummy);
	section->readStringValue("NeutralTechBuildings", NeutralTechBuildings);


	allocateList(BuildingType::Array, BuildConst);
	allocateList(BuildingType::Array, BuildPower);
	allocateList(BuildingType::Array, BuildRefinery);
	allocateList(BuildingType::Array, BuildBarracks);
	allocateList(BuildingType::Array, BuildTech);
	allocateList(BuildingType::Array, BuildWeapons);
	allocateList(BuildingType::Array, AlliedBaseDefenses);
	allocateList(BuildingType::Array, SovietBaseDefenses);
	allocateList(BuildingType::Array, ThirdBaseDefenses);
	allocateList(BuildingType::Array, BuildDefense);
	allocateList(BuildingType::Array, BuildPDefense);
	allocateList(BuildingType::Array, BuildAA);
	allocateList(BuildingType::Array, BuildHelipad);
	allocateList(BuildingType::Array, BuildRadar);
	allocateList(BuildingType::Array, ConcreteWalls);
	allocateList(BuildingType::Array, NSGates);
	allocateList(BuildingType::Array, EWGates);
	allocateList(BuildingType::Array, BuildNavalYard);
	allocateList(BuildingType::Array, BuildDummy);
	allocateList(BuildingType::Array, NeutralTechBuildings);

}