#include "stdafx.h"
#include "MapWriter.h"
#include "../../Log.hpp"
#include "../IniFile/INIFile.hpp"

#include "../../Editor.Engine/Types/VariableName.hpp"
#include "../../Editor.Engine/Types/House.hpp"
#include "../../Editor.Engine/Types/AI/AITriggerEnable.hpp"
#include "../../Editor.Engine/Types/AI/AITriggerType.hpp"
#include "../../Editor.Engine/Types/Triggers/Tag.hpp"
#include "../../Editor.Engine/Types/Triggers/Trigger.hpp"
#include "../../Editor.Engine/Types/Triggers/Event.hpp"
#include "../../Editor.Engine/Types/Triggers/Action.hpp"
#include "../../Editor.Engine/Types/Triggers/CellTag.hpp"
#include "../../Editor.Engine/Types/Waypoint.hpp"
#include "../../Editor.Engine/Types/Objects/Aircraft.hpp"
#include "../../Editor.Engine/Types/Objects/Infantry.hpp"
#include "../../Editor.Engine/Types/Objects/Structure.hpp"
#include "../../Editor.Engine/Types/Objects/Terrain.hpp"
#include "../../Editor.Engine/Types/Objects/Unit.hpp"
#include "../../Editor.Engine/Types/Smudge.hpp"

void MapWriter::writeMap(const std::string& fullFileName)
{
	INIFile aFile;

	VariableName::writeToINI(aFile);
	House::writeToINI(aFile);
	Aircraft::writeToINI(aFile);
	Infantry::writeToINI(aFile);
	Structure::writeToINI(aFile);
	Unit::writeToINI(aFile);
	AITriggerEnable::writeToINI(aFile);
	AITriggerType::writeToINI(aFile);
	Tag::writeToINI(aFile);
	Trigger::writeToINI(aFile);
	Event::writeToINI(aFile);
	Action::writeToINI(aFile);
	CellTag::writeToINI(aFile);
	Waypoint::writeToINI(aFile);
	Terrain::writeToINI(aFile);
	Smudge::writeToINI(aFile);

	aFile.writeToFile(fullFileName, false, true);
}
	/*
		[Basic]
		[SpecialFlags]
		V[VariableNames]
		[Lighting]
		V[Houses]
		Vn type of Houses
		[Countries]
		n type of Countries
		V[Aircraft]
		V[Infantry]
		V[Structures]
		V[Units]
		V[AITriggerTypesEnable]
		V[AITriggerTypes]
		[ScriptTypes]
		n types of ScriptTypes
		[TaskForces]
		n types of TaskForces
		[TeamTypes]
		n types of TeamTypes
		V[Tags]
		V[Triggers]
		V[Events]
		V[Actions]
		V[CellTags]
		V[Waypoints]
		V[Terrain]
		V[Smudge]
		[Map]
		[Header]
		[Preview]
		[PreviewPack]
		[IsoMapPack5]
		[OverlayPack]
		[OverlayDataPack]
		[Digest]
	*/