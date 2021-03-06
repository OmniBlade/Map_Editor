#include "stdafx.h"
#include "MapObjectLoader.hpp"
#include "../../Config.hpp"
#include "../Types/Managers/MapObjectListHelpers.hpp"
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
#include "../Types/Smudge.hpp"
#include "../Types/Waypoint.hpp"
#include "../Types/VariableName.hpp"
#include "../../Editor.FileSystem/IniFile/DigestClass.h"
#include "MapObjectHelper.h"
#include <vector>

MapObjectLoader::MapObjectLoader()
{
}

void MapObjectLoader::clearAll()
{
	clearList(Waypoint::Array);
	clearList(VariableName::Array);
	clearList(House::Array);
	clearList(Action::Array);
	clearList(Event::Array);
	clearList(Trigger::Array);
	clearList(Tag::Array);
	clearList(CellTag::Array);
	clearList(TeamType::Array);
	clearList(ScriptType::Array);
	clearList(TaskForce::Array);
	clearList(AITriggerType::Array);
	clearList(AITriggerEnable::Array);
	clearList(Aircraft::Array);
	clearList(Infantry::Array);
	clearList(Unit::Array);
	clearList(Structure::Array);
	clearList(Terrain::Array);
	clearList(Tube::Array);
	clearList(Smudge::Array);
}

void MapObjectLoader::load(INIFile* mapFile, const std::string& name)
{
	if (!mapFile)
	{
		Log::line("Unable to allocate map objects, '" + name + "' file doesn't exist!", Log::DEBUG);
		return;
	}

	allocateMainData(mapFile, name);
	loadAll(mapFile, name);
}

void MapObjectLoader::allocateMainData(INIFile* mapFile, const std::string& name)
{
	Log::line("Allocating map objects now for '" + name + "'...", Log::DEBUG);

	allocateAll(House::Array, mapFile, "Houses");
	allocateAll(TeamType::Array, mapFile, "TeamTypes");
	allocateAll(TaskForce::Array, mapFile, "TaskForces");
	allocateAll(ScriptType::Array, mapFile, "ScriptTypes");
}

void MapObjectLoader::loadAll(INIFile* mapFile, const std::string& name)
{
	Log::line("Loading map objects now for '" + name + "'...", Log::DEBUG);

	loadFromINI(Waypoint::Array, *mapFile, "Waypoints");
	loadFromINI(VariableName::Array, *mapFile, "VariableNames");
	loadAllocatedINI(House::Array, *mapFile); //WARNING, this is a FOA thing!
	loadFromINI(Action::Array, *mapFile, "Actions");
	loadFromINI(Event::Array, *mapFile, "Events");
	loadFromINI(Trigger::Array, *mapFile, "Triggers");
	loadFromINI(Tag::Array, *mapFile, "Tags");
	loadFromINI(CellTag::Array, *mapFile, "CellTags");
	updateTriggerChilds();
	loadAllocatedINI(TeamType::Array, *mapFile); //WARNING, this is a FOA thing!
	loadAllocatedINI(ScriptType::Array, *mapFile); //WARNING, this is a FOA thing!
	loadAllocatedINI(TaskForce::Array, *mapFile); //WARNING, this is a FOA thing!
	loadFromINI(AITriggerType::Array, *mapFile, "AITriggerTypes");
	loadFromINI(AITriggerEnable::Array, *mapFile, "AITriggerTypesEnable");
	loadFromINI(Aircraft::Array, *mapFile, "Aircraft");
	loadFromINI(Infantry::Array, *mapFile, "Infantry");
	loadFromINI(Unit::Array, *mapFile, "Units");
	loadFromINI(Structure::Array, *mapFile, "Structures");
	loadFromINI(Terrain::Array, *mapFile, "Terrain");
	loadFromINI(Tube::Array, *mapFile, "Tubes");
	loadFromINI(Smudge::Array, *mapFile, "Smudge");
}

/*
	Fucking ape-shit...
	After all the triggers are parsed, you can assign the child triggers
	Why? Because Trigger at index 2 can refer to a Trigger at index 8 (which is obviously not loaded yet)
*/
void MapObjectLoader::updateTriggerChilds()
{
	for (const auto& it : Trigger::Array.objectList)
	{
		it->assignChild();
	}
}

void MapObjectLoader::dumpTypes()
{
	Log::line();
	Log::line("Dumping the count of map types!",Log::DEBUG);
	Log::line("Tags: " + Log::toString(Tag::Array.objectList.size()), Log::DEBUG);
	Log::line("Triggers: " + Log::toString(Trigger::Array.objectList.size()), Log::DEBUG);
	Log::line("Events: " + Log::toString(Event::Array.objectList.size()), Log::DEBUG);
	Log::line("Actions: " + Log::toString(Action::Array.objectList.size()), Log::DEBUG);
	Log::line("TeamTypes: " + Log::toString(TeamType::Array.objectList.size()), Log::DEBUG);
	Log::line("ScriptType: " + Log::toString(ScriptType::Array.objectList.size()), Log::DEBUG);
	Log::line("TaskForces: " + Log::toString(TaskForce::Array.objectList.size()), Log::DEBUG);
}

void MapObjectLoader::setGlobalValues()
{
	for (auto& it : VariableName::Array.objectList)
	{
		it->isGlobal = true;
	}

	for (auto& it : Trigger::Array.objectList)
	{
		it->isGlobal = true;
	}

	for (auto& it : Tag::Array.objectList)
	{
		it->isGlobal = true;
	}

	for (auto& it : Event::Array.objectList)
	{
		it->isGlobal = true;
	}

	for (auto& it : Action::Array.objectList)
	{
		it->isGlobal = true;
	}

	for (auto& it : AITriggerType::Array.objectList)
	{
		it->isGlobal = true;
	}

	for (auto& it : House::Array.objectList)
	{
		it->isGlobal = true;
	}

	for (auto& it : TeamType::Array.objectList)
	{
		it->isGlobal = true;
	}

	for (auto& it : TaskForce::Array.objectList)
	{
		it->isGlobal = true;
	}

	for (auto& it : ScriptType::Array.objectList)
	{
		it->isGlobal = true;
	}
}
