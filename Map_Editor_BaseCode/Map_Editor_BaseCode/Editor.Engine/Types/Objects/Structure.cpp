#include "stdafx.h"
#include "Structure.hpp"
#include <sstream>
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Editor.Objects.Westwood/Types/BuildingType.hpp"
#include "../../../Editor.Objects.Westwood/Types/Country.hpp"
#include "../Triggers/Tag.hpp"
#include "../House.hpp"

/* static */ MapObjectList<Structure> Structure::Array;

Structure::Structure()
{

}

void Structure::parse(const std::string& index, const std::string& list)
{
	LineSplitter split(list);
	if (split.pop(owner) && split.pop(buildingType) && split.pop(health) && split.pop(loc.x) && split.pop(loc.y)
		&& split.pop(direction) && split.pop(tag) && split.pop(sellable) && split.pop(aiRepair) && split.pop(powered) 
		&& split.pop(powerupCount) && split.pop(spotlight) && split.pop(powerupOne) && split.pop(powerupTwo)
		&& split.pop(powerupThree) && split.pop(rebuild) && split.pop(showName))
	{
		//9=Pacific House     ,GAPOWR,256,117,191,64,None,1,0,1,1,       0,GAPOWRUP,None,None,1,0
		//0=UnitedStates House,GAPOWR,256,67,71,64  ,None,1,0,1,UPGRADES,0,GAPOWRUP,None,None,0,0
		pBuilding = BuildingType::Array.find(buildingType);
		pTag = Tag::Array.find(tag);
		pCountry = Country::Array.find(owner);
		pHouse = House::Array.find(owner);
	}
	else
	{
		Log::line("Unable to parse Structure with entry number '" + index + "'.", Log::DEBUG);
	}
}

std::string Structure::asString() const
{
	std::stringstream structureStream;
	structureStream << owner << ',' << buildingType << ',' << health << ',' << loc.x << ',' << loc.y << ',' << direction
		<< ',' << tag << ',' << sellable << ',' << aiRepair << ',' << powered << ',' << powerupCount << ',' << spotlight
		<< ',' << powerupOne << ',' << powerupTwo << ',' << powerupThree << ',' << rebuild << ',' << showName;

	return structureStream.str();
}

void Structure::setBuildingType()
{
	pBuilding = BuildingType::Array.find(buildingType);
}