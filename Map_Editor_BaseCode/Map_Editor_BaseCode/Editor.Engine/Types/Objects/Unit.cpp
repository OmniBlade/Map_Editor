#include "stdafx.h"
#include "Unit.hpp"
#include <sstream>
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Editor.Objects.Westwood/Types/VehicleType.hpp"
#include "../../../Editor.Objects.Westwood/Types/Country.hpp"
#include "../Triggers/Tag.hpp"
#include "../House.hpp"

/* static */ ObjectList<Unit> Unit::Array;

Unit::Unit()
{
}

void Unit::parse(const std::string& index, const std::string& list)
{
	LineSplitter split(list);
	if (split.pop(owner) && split.pop(vehicleType) && split.pop(health) && split.pop(loc.x) && split.pop(loc.y)
		&& split.pop(direction) && split.pop(mission) && split.pop(tag) && split.pop(veterancy) && split.pop(group)
		&& split.pop(onBridge) && split.pop(followsID) && split.pop(recruitable) && split.pop(aiRecruitable))
	{
		pVehicle = VehicleType::Array.find(vehicleType);
		pTag = Tag::Array.find(tag);
		pCountry = Country::Array.find(owner);
		pHouse = House::Array.find(owner);
	}
	else
	{
		Log::note("Unable to parse Unit with entry number '" + index + "'.", Log::DEBUG);
	}
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
