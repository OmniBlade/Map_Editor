#include "stdafx.h"
#include "MapWriter.h"
#include "../IniFile/INIFile.hpp"
#include "../../Log.hpp"
#include "../../Editor.Engine/Basics/Basic.hpp"
#include "../../Editor.Engine/Basics/Ranking.h"
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
#include "../../Editor.Engine/Map/Packs/IsoMapPack.hpp"
#include "../../Editor.Engine/Map/Packs/OverlayPack.hpp"
#include "../../Editor.Engine/Map/Packs/PreviewPack.h"
#include "../../Config.hpp"
#include "Modifications/MapMods.h"
#include "Flushing/NameFlusherClass.h"

void MapWriter::writeAll(const std::string& fullFileName)
{
	unstableMessage = "THIS IS A FILE CREATED BY AN UNSTABLE BUILD OF THE EDITOR - BUGS ARE TO BE EXPECTED";
	writeMap(fullFileName);
	
	if(Basic::getBasic()->NamesFlushed) 
		writeNamesFile(fullFileName);
}

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
	aFile.addCommentAtTop(unstableMessage);

	auto flushNames = Basic::getBasic()->NamesFlushed;

	Country::writeToINI(aFile);
	//Header
	SpecialFlag::writeToINI(aFile);
	Ranking::writeToINI(aFile);
	Basic::writeToINI(aFile);
	VariableName::writeToINI(aFile, flushNames);	//Flush names
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
	ScriptType::writeToINI(aFile, flushNames);		//Flush names
	TaskForce::writeToINI(aFile, flushNames);		//Flush names
	TeamType::writeToINI(aFile, flushNames);		//Flush names
	AITriggerType::writeToINI(aFile, flushNames);	//Flush names
	AITriggerEnable::writeToINI(aFile);
	Trigger::writeToINI(aFile, flushNames);			//Flush names
	Event::writeToINI(aFile);			
	Action::writeToINI(aFile);	
	Tag::writeToINI(aFile, flushNames);				//Flush names
	MapMods::writeToINI(aFile);
	
	//With Digest, ordered non-alphabetical (like how it is done right above this line)
	aFile.writeToFile(fullFileName);

	Log::line("Map succesfully written!", Log::DEBUG);
}

void MapWriter::writeNamesFile(const std::string& fullFileName)
{
	INIFile namesFile;

	namesFile.addCommentAtTop("Map Editor 2014 - Red Alert 2 & Yuri's Revenge build");
	namesFile.addCommentAtTop("All hail the Mapping God RP!");
	namesFile.addCommentAtTop("This file contains the names of the given types for '" + namesFileName +"'.");
	namesFile.addCommentAtTop("");
	namesFile.addCommentAtTop(unstableMessage);

	NameFlusherClass::writeToFile(namesFile);
	namesFile.writeToFile(fullFileName + Config::namesName);
}