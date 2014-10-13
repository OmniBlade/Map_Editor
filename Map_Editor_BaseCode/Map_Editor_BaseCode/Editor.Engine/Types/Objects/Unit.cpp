#include "stdafx.h"
#include "Unit.hpp"
#include <sstream>
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Editor.Objects.Westwood/Types/VehicleType.hpp"
#include "../../../Editor.Objects.Westwood/Types/Country.hpp"
#include "../Triggers/Tag.hpp"
#include "../House.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"

/* static */ MapObjectList<Unit> Unit::Array;

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
		Log::line("Unable to parse Unit with entry number '" + index + "'.", Log::DEBUG);
	}
}

void Unit::writeToINI(INIFile& file)
{
	std::stringstream number;
	int i = 0;
	for (auto& it : Array.objectList)
	{
		number << i;
		file.SetValue("Units", number.str(), it->asString());
		++i;
		number.str(std::string());
	}
}

std::string Unit::asString() const
{
	char buffer[512];
	//Don't need to include the ID, so no "%s = "
	sprintf_s(buffer, 512, "%s,%s,%d,%d,%d,%d,%s,%s,%d,%d,%d,%d,%d,%d",
		this->owner.c_str(),
		this->vehicleType.c_str(),
		this->health,
		this->loc.x,
		this->loc.y,
		this->direction,
		this->mission.c_str(),
		this->tag.c_str(),
		this->veterancy,
		this->group,
		this->onBridge != 0,
		this->followsID,
		this->recruitable != 0,
		this->aiRecruitable != 0
		);

	return buffer;
}

void Unit::setVehicleType()
{
	pVehicle = VehicleType::Array.find(vehicleType);
}
