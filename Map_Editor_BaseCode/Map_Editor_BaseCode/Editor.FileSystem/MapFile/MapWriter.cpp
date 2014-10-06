#include "stdafx.h"
#include "MapWriter.h"
#include "../../Log.hpp"

void MapWriter::writeMap(const std::string& fullFileName)
{
	mapStream.open(fullFileName);
	
	if (!mapStream.is_open())
	{
		Log::line("CRITICAL - Unable to write map to file with path and name: " + fullFileName, Log::DEBUG);
		return;
	}

	writeMapMods();
	writeBasicSections();
	writeObjectSections();
	writeAISections();
	writeCoreSections();
	writeTriggerSections();

}

void MapWriter::writeBasicSections()
{
	/*
		[Basic]
		[SpecialFlags]
		[VariableNames]
		[Lighting]
		[Houses]
		n type of Houses
		[Countries]
		n type of Countries
	*/
}

void MapWriter::writeCoreSections()
{
	/*
		[Map]
		[Header]
		[Preview]
		[PreviewPack]
		[IsoMapPack5]
		[OverlayPack]
		[OverlayDataPack]
	*/
}

void MapWriter::writeAISections()
{
	/*
		[ScriptTypes]
		n types of ScriptTypes
		[TaskForces]
		n types of TaskForces
		[TeamTypes]
		n types of TeamTypes
		[AITriggerTypesEnable]
		[AITriggerTypes]
	*/
}

void MapWriter::writeTriggerSections()
{
	/*
		[Tags]
		[Triggers]
		[Events]
		[Actions]
		[CellTags]
		[Waypoints]
	*/
}

void MapWriter::writeObjectSections()
{
	/*
		[Aircraft]
		[Infantry]
		[Structures]
		[Units]
		[Terrain]
		[Smudge]
	*/
}

void MapWriter::writeDigest()
{
	/*
		[Digest]
	*/
}