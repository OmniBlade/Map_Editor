#include "stdafx.h"
#include "Infantry.hpp"
#include <sstream>

Infantry::Infantry()
{
}

std::string Infantry::asString() const
{
	std::stringstream infantryStream;
	infantryStream << owner << ',' << infantryType << ',' << health << ',' << loc.x << ',' << loc.y << ',' << subCell
		<< ',' << mission << ',' << direction << ',' << tag << ',' << veterancy << ',' << group << ',' << onBridge
		<< ',' << recruitable << ',' << aiRecruitable;

	return infantryStream.str();
}