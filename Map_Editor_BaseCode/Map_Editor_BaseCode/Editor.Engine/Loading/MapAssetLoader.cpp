#include "stdafx.h"
#include "MapAssetLoader.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Config.hpp"
#include "../Types/Managers/ObjectListHelpers.hpp"
#include "../Types/AI/AITriggerEnable.hpp"
#include "../Types/AI/AITriggerType.hpp"
#include "../Types/House.hpp"
#include "../Types/Objects/Aircraft.hpp"
#include "../Types/Objects/Structure.hpp"
#include "../Types/Objects/Unit.hpp"
#include "../Types/Objects/Infantry.hpp"
#include "../Types/Objects/Terrain.hpp"
#include "../Types/TeamTypes/ScriptType.hpp"
#include "../Types/TeamTypes/TaskForce.hpp"
#include "../Types/TeamTypes/TeamType.hpp"
#include "../Types/Triggers/CellTag.hpp"
#include "../Types/Triggers/Tag.hpp"
#include "../Types/Triggers/Trigger.hpp"
#include "../Types/Triggers/Action.hpp"
#include "../Types/Triggers/Event.hpp"
#include "../Types/Tube.hpp"
#include "../Types/Waypoint.hpp"
#include "../Types/VariableName.hpp"

MapAssetLoader::MapAssetLoader()
{
}

void MapAssetLoader::load(INIFile* mapFile)
{
	if (!mapFile)
	{
		Log::note("Unable to allocate map objects, file doesn't exist!", Log::DEBUG);
		return;
	}

	allocateMainData(mapFile);
	loadAll(mapFile);
}

void MapAssetLoader::loadAI()
{
	if (!Config::AIReferences)
	{
		return;
	}
	else
	{
		Log::note("Loading AI content from '" + Config::AI + "'.", Log::DEBUG);
	}

	INIFile* aimd = INIManager::getManager()->get(Config::AI);
	allocateAll(TeamType::Array, aimd, "TeamTypes");
	allocateAll(TaskForce::Array, aimd, "TaskForces");
	allocateAll(ScriptType::Array, aimd, "ScriptTypes");
	loadAllocatedINI(TeamType::Array, *aimd, true);
	loadAllocatedINI(TaskForce::Array, *aimd, true);
	loadAllocatedINI(ScriptType::Array, *aimd, true);
}

void MapAssetLoader::allocateMainData(INIFile* mapFile)
{
	allocateAll(House::Array, mapFile, "Houses");
	allocateAll(TeamType::Array, mapFile, "TeamTypes");
	allocateAll(TaskForce::Array, mapFile, "TaskForces");
	allocateAll(ScriptType::Array, mapFile, "ScriptTypes");
}

void MapAssetLoader::loadAll(INIFile* mapFile)
{
	Log::note("Loading map objects now...", Log::DEBUG);

	loadFromINI(Waypoint::Array, *mapFile, "Waypoints");
	loadFromINI(VariableName::Array, *mapFile, "VariableNames");
	loadAllocatedINI(House::Array, *mapFile); //WARNING, this is a FOA thing!
	loadFromINI(Tag::Array, *mapFile, "Tags");
	loadFromINI(CellTag::Array, *mapFile, "CellTags");
	loadFromINI(Trigger::Array, *mapFile, "Triggers");
	loadFromINI(Action::Array, *mapFile, "Actions");
	loadFromINI(Event::Array, *mapFile, "Events");
	loadAllocatedINI(TeamType::Array, *mapFile); //WARNING, this is a FOA thing!
	loadAllocatedINI(ScriptType::Array, *mapFile); //WARNING, this is a FOA thing!
	loadAllocatedINI(TaskForce::Array, *mapFile); //WARNING, this is a FOA thing!
	loadFromINI(AITriggerEnable::Array, *mapFile, "AITriggerEnable");
	loadFromINI(AITriggerType::Array, *mapFile, "AITriggerTypes");
	loadFromINI(Aircraft::Array, *mapFile, "Aircraft");
	loadFromINI(Infantry::Array, *mapFile, "Infantry");
	loadFromINI(Unit::Array, *mapFile, "Units");
	loadFromINI(Structure::Array, *mapFile, "Structures");
	loadFromINI(Terrain::Array, *mapFile, "Terrain");
	loadFromINI(Tube::Array, *mapFile, "Tubes");
}