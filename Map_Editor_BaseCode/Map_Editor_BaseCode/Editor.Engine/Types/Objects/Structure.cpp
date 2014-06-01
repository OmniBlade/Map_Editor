#include "stdafx.h"
#include "Structure.hpp"
#include <sstream>
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Editor.Objects.Westwood/Types/BuildingType.hpp"
#include "../Triggers/Tag.hpp"

/* static */ ObjectList<Structure> Structure::Array;

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
		pBuilding = BuildingType::Array.find(buildingType);
		pTag = Tag::Array.find(tag);
	}
	else
	{
		Log::note("Unable to parse Structure with entry number '" + index + "'.", Log::DEBUG);
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