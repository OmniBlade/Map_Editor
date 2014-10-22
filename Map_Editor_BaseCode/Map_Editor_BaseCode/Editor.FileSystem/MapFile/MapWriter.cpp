#include "stdafx.h"
#include "MapWriter.h"
#include "../../Log.hpp"
#include "../IniFile/INIFile.hpp"
#include "../../Editor.Engine/Basics/Basic.hpp"
#include "../../Editor.Engine/Basics/Lighting.hpp"
#include "../../Editor.Engine/Basics/SpecialFlag.hpp"
#include "../../Editor.Engine/Types/VariableName.hpp"
#include "../../Editor.Engine/Types/House.hpp"
#include "../../Editor.Objects.Westwood/Types/Country.hpp"
#include "../../Editor.Engine/Types/AI/AITriggerEnable.hpp"
#include "../../Editor.Engine/Types/AI/AITriggerType.hpp"
#include "../../Editor.Engine/Types/TeamTypes/ScriptType.hpp"
#include "../../Editor.Engine/Types/TeamTypes/TaskForce.hpp"
#include "../../Editor.Engine/Types/TeamTypes/TeamType.hpp"
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
#include "../../Editor.Engine/Types/Tube.hpp"
#include "../../Editor.Engine/Basics/MapStats.hpp"
#include "../../Editor.Engine/Map/IsoMapPack.hpp"
#include "../../Editor.Engine/Map/OverlayPack.hpp"
#include "../../Editor.Engine/Map/PreviewPack.h"
#include "../IniFile/DigestClass.h"
#include "MapMods.h"

void MapWriter::writeMap(const std::string& fullFileName)
{
	INIFile aFile;

	Log::line();
	Log::line("Writing map now!", Log::DEBUG);
	Log::line("Writing to: " + fullFileName, Log::DEBUG);

	aFile.addCommentAtTop("Map Editor 2014 - Red Alert 2 & Yuri's Revenge build");
	aFile.addCommentAtTop("All hail the Mapping God RP!");
	aFile.addCommentAtTop("You've viewed all map modifications when SpecialFlags or Header section starts.");
	aFile.addCommentAtTop("");
	aFile.addCommentAtTop("THIS IS A MAP CREATED BY AN UNSTABLE BUILD OF THE EDITOR - BUGS ARE TO BE EXPECTED");

	Country::writeToINI(aFile);
	//Header
	SpecialFlag::writeToINI(aFile);
	//Ranking
	Basic::writeToINI(aFile);
	VariableName::writeToINI(aFile);
	Lighting::writeToINI(aFile);	
	PreviewPack::writeToINI(aFile);
	House::writeToINI(aFile);
	MapStats::writeToINI(aFile);
	Waypoint::writeToINI(aFile);
	CellTag::writeToINI(aFile);
	IsoMapPack::writeToINI(aFile);
	Tube::writeToINI(aFile);
	Terrain::writeToINI(aFile);
	Unit::writeToINI(aFile);
	Infantry::writeToINI(aFile);
	Structure::writeToINI(aFile);
	Aircraft::writeToINI(aFile);
	OverlayPack::writeToINI(aFile);
	Smudge::writeToINI(aFile);
	ScriptType::writeToINI(aFile);
	TaskForce::writeToINI(aFile);	
	TeamType::writeToINI(aFile);
	AITriggerType::writeToINI(aFile);
	AITriggerEnable::writeToINI(aFile);
	Trigger::writeToINI(aFile);
	Event::writeToINI(aFile);
	Action::writeToINI(aFile);
	Tag::writeToINI(aFile);
	MapMods::writeToINI(aFile);
	//MapMods::writeCountriesToINI(aFile); // Country::writeToINI(aFile);

	//With Digest, ordered non-alphabetical (like how it is done right above this line)
	aFile.writeToFile(fullFileName, true, false);

	Log::line("Map succesfully written!", Log::DEBUG);

}
	/*
		V[Basic]
		V[SpecialFlags]
		V[Lighting]
		V[VariableNames]
		V[Houses]
		Vn type of Houses
		V[Countries]
		Vn type of Countries
		V[Aircraft]
		V[Infantry]
		V[Structures]
		V[Units]
		V[AITriggerTypesEnable]
		V[AITriggerTypes]
		V[ScriptTypes]
		Vn types of ScriptTypes
		V[TaskForces]
		Vn types of TaskForces
		V[TeamTypes]
		Vn types of TeamTypes
		V[Tags]
		V[Triggers]
		V[Events]
		V[Actions]
		V[CellTags]
		V[Waypoints]
		V[Terrain]
		V[Smudge]
		V[Tubes]
		V[Map]
		[Header]
		V[Preview] -- Size of the picture
		V[PreviewPack] -- Size.x * Size.y sized
		V[IsoMapPack5]
		V[OverlayPack]
		V[OverlayDataPack]
		V[Digest]
	*/