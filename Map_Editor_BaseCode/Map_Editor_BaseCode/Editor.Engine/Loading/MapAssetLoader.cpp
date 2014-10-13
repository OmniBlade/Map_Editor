#include "stdafx.h"
#include "MapAssetLoader.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
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
		Log::line("Unable to allocate map objects, file doesn't exist!", Log::DEBUG);
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
	Log::line("Loading map objects now...", Log::DEBUG);

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
void MapAssetLoader::updateTriggerChilds()
{
	for (const auto& it : Trigger::Array.objectList)
	{
		it.get()->assignChild();
	}
}

void MapAssetLoader::dumpTypes()
{
	Log::line();
	Log::line("Dumping the count of map types!");
	Log::line("Tags: " + Log::toString(Tag::Array.objectList.size()), Log::DEBUG);
	Log::line("Triggers: " + Log::toString(Trigger::Array.objectList.size()), Log::DEBUG);
	Log::line("Events: " + Log::toString(Event::Array.objectList.size()), Log::DEBUG);
	Log::line("Actions: " + Log::toString(Action::Array.objectList.size()), Log::DEBUG);
	Log::line("TeamTypes: " + Log::toString(TeamType::Array.objectList.size()), Log::DEBUG);
	Log::line("ScriptType: " + Log::toString(ScriptType::Array.objectList.size()), Log::DEBUG);
	Log::line("TaskForces: " + Log::toString(TaskForce::Array.objectList.size()), Log::DEBUG);
	Log::line();
}

void MapAssetLoader::loadOverlay(INIFile* mapFile)
{

	return;

	Log::line("KEKEKEKE", Log::DEBUG);
	std::vector<byte> overlayData, overlayPack;

	PackType anOverlayPack(mapFile->getSection("OverlayPack"), PackType::F80);
	PackType anOverlayDataPack(mapFile->getSection("OverlayDataPack"), PackType::F80);

	anOverlayDataPack.decode64();
	anOverlayPack.decode64();

	anOverlayDataPack.decompress();
	anOverlayPack.decompress();

	overlayData = anOverlayDataPack.getReadDest();
	overlayPack = anOverlayPack.getReadDest();

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

	auto dest = anOverlayPack.getReadDest();

	anOverlayPack.setWriteSrc(anOverlayPack.getReadDest());

	anOverlayPack.setWriteSrc(anOverlayPack.getReadDest());
	anOverlayPack.compress();

	anOverlayPack.setReadSrc(anOverlayPack.getWriteDest());
	anOverlayPack.decompress();

	auto dest2 = anOverlayPack.getReadDest();


}