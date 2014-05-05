#include "stdafx.h"
#include "Structure.hpp"
#include <sstream>

Structure::Structure()
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