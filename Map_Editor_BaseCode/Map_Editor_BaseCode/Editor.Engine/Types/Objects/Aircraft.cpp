#include "stdafx.h"
#include "Aircraft.hpp"
#include <sstream>
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Editor.Objects.Westwood/Types/AircraftType.hpp"
#include "../../../Editor.Objects.Westwood/Types/Country.hpp"
#include "../Triggers/Tag.hpp"
#include "../House.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"

/* static */ MapObjectList<Aircraft> Aircraft::Array;


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
		Log::line("Unable to parse Aircraft with entry number '" + index + "'.", Log::DEBUG);
	}
}

void Aircraft::writeToINI(INIFile& file)
{
	if (Array.objectList.size() == 0)
	{
		Log::line("SECTION - Aircraft does not exist, will not write to map.", Log::DEBUG);
		return;
	}

	std::stringstream number;
	int i = 0;
	for (auto& it : Array.objectList)
	{
		number << i;
		file.SetValue("Aircraft", number.str(), it->asString());
		++i;
		number.str(std::string());
	}
}

std::string Aircraft::asString() const
{
	char buffer[512];
	//Don't need to include the ID, so no "%s = "
	sprintf_s(buffer, 512, "%s,%s,%d,%d,%d,%d,%s,%s,%d,%d,%d,%d",
		this->owner.c_str(),
		this->aircraftType.c_str(),
		this->health,
		this->loc.x,
		this->loc.y,
		this->direction,
		this->mission.c_str(),
		this->tag.c_str(),
		this->veterancy,
		this->group,
		this->recruitable != 0,
		this->aiRecruitable != 0
		);

	return buffer;
}

void Aircraft::setAircraftType()
{
	pAircraft = AircraftType::Array.find(aircraftType);
}