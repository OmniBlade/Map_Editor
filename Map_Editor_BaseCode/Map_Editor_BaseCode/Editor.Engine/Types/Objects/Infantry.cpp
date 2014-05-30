#include "stdafx.h"
#include "Infantry.hpp"
#include <sstream>

/* static */ ObjectList<Infantry> Infantry::Array;

Infantry::Infantry()
{
}

void Infantry::parse(const std::string& index, const std::string& list)
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

void ::Infantry::setInfantryType()
{
	pInfantry = InfantryType::Array.find(infantryType);
}