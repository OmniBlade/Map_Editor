#include "stdafx.h"
#include "MapMods.h"
#include "../../Editor.Engine/Types/Managers/MapObjectList.hpp"
#include "../../Editor.Objects.Westwood/Managers/WWList.hpp"
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
	for (auto& it : instance->modsFile->getSectionList())
	{
		file.addSectionByCopy(instance->modsFile->getSection(it));
	}
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
	mapSections.clear();

	mapSections.push_back("Basic");
	mapSections.push_back("SpecialFlags");
	mapSections.push_back("Lighting");
	mapSections.push_back("VariableNames");
	mapSections.push_back("Houses");
	fillMapSection(this, House::Array);
	mapSections.push_back("Countries");
	fillMapSection(this, Country::Array);
	mapSections.push_back("Aircraft");
	mapSections.push_back("Infantry");
	mapSections.push_back("Structures");
	mapSections.push_back("Units");
	mapSections.push_back("AITriggerTypesEnable");
	mapSections.push_back("AITriggerTypes");
	fillMapSection(this, AITriggerType::Array);
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
	mapSections.push_back("Header");
}
