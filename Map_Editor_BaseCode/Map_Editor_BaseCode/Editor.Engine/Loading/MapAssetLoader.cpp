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
#include "../Types/Overlay.h"
#include "../Types/Tube.hpp"
#include "../Types/Smudge.hpp"
#include "../Types/Waypoint.hpp"
#include "../Types/VariableName.hpp"
#include "../Map/PackType.hpp"
#include <vector>

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
	loadFromINI(Action::Array, *mapFile, "Actions");
	loadFromINI(Event::Array, *mapFile, "Events");
	loadFromINI(Trigger::Array, *mapFile, "Triggers");
	loadFromINI(Tag::Array, *mapFile, "Tags");
	loadFromINI(CellTag::Array, *mapFile, "CellTags");
	updateTriggerChilds();
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
	loadFromINI(Smudge::Array, *mapFile, "Smudge");
}

/*
Fucking ape-shit...
After all the triggers are parsed, you can assign the child triggers
Why? Because Trigger at index 2 can refer to a Trigger at index 8 (which is obviously not loaded yet)
*/
void MapAssetLoader::updateTriggerChilds()
{
	for (const auto& it : Trigger::Array.objectTypeList)
	{
		it.get()->assignChild();
	}
}

void MapAssetLoader::dumpTypes()
{
	Log::note();
	Log::note("Dumping the count of map types!");
	Log::note("Tags: " + Log::toString(Tag::Array.objectTypeList.size()), Log::DEBUG);
	Log::note("Triggers: " + Log::toString(Trigger::Array.objectTypeList.size()), Log::DEBUG);
	Log::note("Events: " + Log::toString(Event::Array.objectTypeList.size()), Log::DEBUG);
	Log::note("Actions: " + Log::toString(Action::Array.objectTypeList.size()), Log::DEBUG);
	Log::note("TeamTypes: " + Log::toString(TeamType::Array.objectTypeList.size()), Log::DEBUG);
	Log::note("ScriptType: " + Log::toString(ScriptType::Array.objectTypeList.size()), Log::DEBUG);
	Log::note("TaskForces: " + Log::toString(TaskForce::Array.objectTypeList.size()), Log::DEBUG);
	Log::note();
}

void MapAssetLoader::loadOverlay(INIFile* mapFile)
{
	std::vector<byte> overlayData, overlayPack;

	PackType anOverlayPack(mapFile->getSection("OverlayPack"), PackType::F80);
	PackType anOverlayDataPack(mapFile->getSection("OverlayDataPack"), PackType::F80);

	anOverlayDataPack.decompress();
	anOverlayPack.decompress();

	overlayData = anOverlayDataPack.getDest();
	overlayPack = anOverlayPack.getDest();

	int x = 0, y = 0;

	for (unsigned int i = 0; i < 511; ++i, ++x)
	{
		for (unsigned int j = 0; j < 511; ++j, ++y)
		{
			if (overlayPack[x + y] != 0xFF)
			{
				Overlay::Array.createOverlay(x, j, overlayPack[x + y], overlayData[x+y]);
			}
		}
	}


}