#include "stdafx.h"
#include "Aircraft.hpp"
#include <sstream>

/* static */ ObjectList<Aircraft> Aircraft::Array;

Aircraft::Aircraft()
{
}

void Aircraft::parse(const std::string& index, const std::string& list)
{

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