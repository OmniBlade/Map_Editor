#include "stdafx.h"
#include "MapMods.h"
#include "../../Editor.Engine/Types/Managers/MapObjectList.hpp"
#include "../../Editor.Objects.Westwood/Types/OverlayType.hpp"
#include "../../Editor.Objects.Westwood/Types/SuperWeaponType.hpp"
#include "../../Editor.Objects.Westwood/Types/WarheadType.hpp"
#include "../../Editor.Objects.Westwood/Types/SmudgeType.hpp"
#include "../../Editor.Objects.Westwood/Types/TerrainType.hpp"
#include "../../Editor.Objects.Westwood/Types/BuildingType.hpp"
#include "../../Editor.Objects.Westwood/Types/VehicleType.hpp"
#include "../../Editor.Objects.Westwood/Types/InfantryType.hpp"
#include "../../Editor.Objects.Westwood/Types/AircraftType.hpp"
#include "../../Editor.Objects.Westwood/Types/Animation.hpp"
#include "../../Editor.Objects.Westwood/Types/VoxelAnimType.hpp"
#include "../../Editor.Objects.Westwood/Types/ParticleType.hpp"
#include "../../Editor.Objects.Westwood/Types/WeaponType.hpp"
#include "MapModsHelper.h"
#include "../INIFile/INIFile.hpp"
#include "../FileManager/Managers/INIManager.hpp"
#include "../../Editor.Engine/Types/House.hpp"
#include "../../Editor.Objects.Westwood/Types/Country.hpp"
#include "../../Editor.Engine/Types/AI/AITriggerType.hpp"
#include "../../Editor.Engine/Types/TeamTypes/ScriptType.hpp"
#include "../../Editor.Engine/Types/TeamTypes/TeamType.hpp"
#include "../../Editor.Engine/Types/TeamTypes/TaskForce.hpp"
#include "../FileManager/Managers/INIManager.hpp"
#include "../../Config.hpp"


/* static */ MapMods* MapMods::instance;

MapMods::MapMods()
{
	instance = this;
	fillMapSections();

	modsFile = INIManager::instance()->insertEmpty(Config::mapModsName);
}


MapMods::~MapMods()
{
}

void MapMods::writeToINI(INIFile& file)
{
	instance->writeGenericSections(file);
	instance->writeFoaSections(file);

	for (auto& it : instance->modsFile->getSectionList())
	{
		if (std::find(instance->writtenSections.begin(), instance->writtenSections.end(), it) == instance->writtenSections.end())
			file.addSectionByCopy(instance->modsFile->getSection(it));

	}

	instance->writtenSections.clear();
}

void MapMods::parse(INIFile* map)
{
	for (const auto& it : map->getSectionList())
	{
		//If it is not a map specific section, it is a map mod!
		if (!isAMapSection(it))
		{
			//This might need a rework
			modsFile->addSectionByCopy(map->getSection(it));
		}
	}
}

bool MapMods::isAMapSection(const std::string& sectionName)
{
	return std::find(mapSections.begin(), mapSections.end(), sectionName) != mapSections.end() ? true : false;
}

void MapMods::fillMapSections()
{
	if (!mapSections.empty())
	{
		return;
	}

	mapSections.clear();

	mapSections.push_back("Basic");
	mapSections.push_back("SpecialFlags");
	mapSections.push_back("Lighting");
	mapSections.push_back("VariableNames");
	mapSections.push_back("Houses");
	fillMapSection(this, House::Array);
	/* Ehm... We're not using all data, so assume it is a map mod, when writing everything will be overwritten by the actual Countries anyhow*/
	mapSections.push_back("Countries"); 
	fillMapSection(this, Country::Array);
	mapSections.push_back("Aircraft");
	mapSections.push_back("Infantry");
	mapSections.push_back("Structures");
	mapSections.push_back("Units");
	mapSections.push_back("AITriggerTypesEnable");
	mapSections.push_back("AITriggerTypes");
	mapSections.push_back("ScriptTypes");
	fillMapSection(this, ScriptType::Array);
	mapSections.push_back("TaskForces");
	fillMapSection(this, TaskForce::Array);
	mapSections.push_back("TeamTypes");
	fillMapSection(this, TeamType::Array);
	mapSections.push_back("Tags");
	mapSections.push_back("Triggers");
	mapSections.push_back("Events");
	mapSections.push_back("Actions");
	mapSections.push_back("CellTags");
	mapSections.push_back("Waypoints");
	mapSections.push_back("Terrain");
	mapSections.push_back("Smudge");
	mapSections.push_back("Tubes");
	mapSections.push_back("Map");
	mapSections.push_back("Preview");
	mapSections.push_back("PreviewPack");
	mapSections.push_back("IsoMapPack5");
	mapSections.push_back("OverlayPack");
	mapSections.push_back("OverlayDataPack");
	mapSections.push_back("Ranking");
	mapSections.push_back("Digest");
	//mapSections.push_back("Header");
}

void MapMods::writeGenericSections(INIFile& file)
{
	auto pGeneral = modsFile->getSection("General");
	if (pGeneral)
	{
		file.addSectionByCopy(pGeneral);
		writtenSections.push_back("General");
	}

	auto pAVisual = modsFile->getSection("AudioVisual");
	if (pAVisual)
	{
		file.addSectionByCopy(pAVisual);
		writtenSections.push_back("AudioVisual");
	}


}

void MapMods::writeFoaSections(INIFile& file)
{
	writeAFoaSection(OverlayType::Array, "OverlayTypes", file);
	writeAFoaSection(SuperWeaponType::Array, "SuperWeaponTypes", file);
	writeAFoaSection(WarheadType::Array, "Warheads", file);
	writeAFoaSection(SmudgeType::Array, "SmudgeTypes", file);
	writeAFoaSection(TerrainType::Array, "TerrainTypes", file);
	writeAFoaSection(BuildingType::Array, "BuildingTypes", file);
	writeAFoaSection(VehicleType::Array,"VehicleTypes", file);
	writeAFoaSection(AircraftType::Array, "AircraftTypes", file);
	writeAFoaSection(InfantryType::Array, "InfantryTypes", file);
	writeAFoaSection(Animation::Array, "Animations", file);
	writeAFoaSection(VoxelAnimType::Array, "VoxelAnims", file);
	writeAFoaSection(ParticleType::Array, "Particles", file);
	writeAFoaSection(WeaponType::Array, "DUMMY :D", file);
}
