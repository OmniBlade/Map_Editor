#include "stdafx.h"
#include "Aircraft.hpp"
#include <sstream>
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Editor.Objects.Westwood/Types/AircraftType.hpp"
#include "../../../Editor.Objects.Westwood/Types/Country.hpp"
#include "../Triggers/Tag.hpp"
#include "../House.hpp"

/* static */ ObjectList<Aircraft> Aircraft::Array;


/*
	Please note:
	Additional constructors will be needed when an object is placed at a specific point with a specific type!
*/

Aircraft::Aircraft()
{
}

void Aircraft::parse(const std::string& index, const std::string& list)
{
	LineSplitter split(list);
	if (split.pop(owner) && split.pop(aircraftType) && split.pop(health) && split.pop(loc.x) && split.pop(loc.y)
		&& split.pop(direction) && split.pop(mission) && split.pop(tag) && split.pop(veterancy) && split.pop(group)
		&& split.pop(recruitable) && split.pop(aiRecruitable))
	{
		pAircraft = AircraftType::Array.find(aircraftType);
		pTag = Tag::Array.find(tag);
		pCountry = Country::Array.find(owner);
		pHouse = House::Array.find(owner);
	}
	else
	{
		Log::note("Unable to parse Aircraft with entry number '" + index + "'.", Log::DEBUG);
	}
}

std::string Aircraft::asString() const
{
	std::stringstream aircraftStream;
	aircraftStream << owner << ',' << aircraftType << ',' << health << ',' << loc.x << ',' << loc.y << ',' << direction
		<< ',' << mission << ',' << tag << ',' << veterancy << ',' << group << ',' << recruitable << ',' << aiRecruitable;

	return aircraftStream.str();
}

void Aircraft::setAircraftType()
{
	pAircraft = AircraftType::Array.find(aircraftType);
}