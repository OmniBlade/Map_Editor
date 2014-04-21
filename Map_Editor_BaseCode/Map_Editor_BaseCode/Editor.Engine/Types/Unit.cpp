#include "stdafx.h"
#include "Unit.hpp"
#include <sstream>

Unit::Unit()
{
}

std::string Unit::asString() const
{
	std::stringstream unitStream;
	unitStream << owner << ',' << vehicleType << ',' << health << ',' << loc.x << ',' << loc.y << ',' << direction
		<< ',' << mission << ',' << tag << ',' << veterancy << ',' << group << ',' << onBridge << ',' << followsID
		<< ',' << recruitable << ',' << aiRecruitable;

	return unitStream.str();
}