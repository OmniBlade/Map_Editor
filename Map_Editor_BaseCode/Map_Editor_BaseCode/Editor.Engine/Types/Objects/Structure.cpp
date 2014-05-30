#include "stdafx.h"
#include "Structure.hpp"
#include <sstream>

/* static */ ObjectList<Structure> Structure::Array;

Structure::Structure()
{

}

void Structure::parse(const std::string& index, const std::string& list)
{

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