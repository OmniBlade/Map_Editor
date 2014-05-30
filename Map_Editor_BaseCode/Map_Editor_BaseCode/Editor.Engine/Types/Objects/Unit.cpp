#include "stdafx.h"
#include "Unit.hpp"
#include <sstream>

/* static */ ObjectList<Unit> Unit::Array;

Unit::Unit()
{
}

void Unit::parse(const std::string& index, const std::string& list)
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

void Unit::setVehicleType()
{
	pVehicle = VehicleType::Array.find(vehicleType);
}
