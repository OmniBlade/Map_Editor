#include "stdafx.h"
#include "Aircraft.hpp"
#include <sstream>

Aircraft::Aircraft()
{
}

std::string Aircraft::asString() const
{
	std::stringstream aircraftStream;
	aircraftStream << owner << ',' << aircraftType << ',' << health << ',' << loc.x << ',' << loc.y << ',' << direction
		<< ',' << mission << ',' << tag << ',' << veterancy << ',' << group << ',' << recruitable << ',' << aiRecruitable;

	return aircraftStream.str();
}