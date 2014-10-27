#include "stdafx.h"
#include "Structure.hpp"
#include <sstream>
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Editor.Objects.Westwood/Types/BuildingType.hpp"
#include "../../../Editor.Objects.Westwood/Types/Country.hpp"
#include "../Triggers/Tag.hpp"
#include "../House.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"

/* static */ MapObjectList<Structure> Structure::Array;

Structure::Structure()
{

}

void Structure::parse(const std::string& index, const std::string& list)
{
	int x, y;
	LineSplitter split(list);
	if (split.pop(owner) && split.pop(buildingType) && split.pop(health) && split.pop(x) && split.pop(y)
		&& split.pop(direction) && split.pop(tag) && split.pop(sellable) && split.pop(aiRepair) && split.pop(powered) 
		&& split.pop(powerupCount) && split.pop(spotlight) && split.pop(powerupOne) && split.pop(powerupTwo)
		&& split.pop(powerupThree) && split.pop(rebuild) && split.pop(showName))
	{
		Object(x, y);
		setObjectType(BuildingType::Array.find(buildingType));
		pTag = Tag::Array.find(tag);
		pCountry = Country::Array.find(owner);
		pHouse = House::Array.find(owner);
	}
	else
	{
		Log::line("Unable to parse Structure with entry number '" + index + "'.", Log::DEBUG);
	}
}

void Structure::writeToINI(INIFile& file)
{
	if (Array.objectList.size() == 0)
	{
		Log::line("SECTION - Structure does not exist, will not write to map.", Log::DEBUG);
		return;
	}

	std::stringstream number;
	int i = 0;
	for (auto& it : Array.objectList)
	{
		number << i;
		file.SetValue("Structures", number.str(), it->asString());
		++i;
		number.str(std::string());
	}
}

std::string Structure::asString() const
{
	char buffer[512];
	//Don't need to include the ID, so no "%s = "
	sprintf_s(buffer, 512, "%s,%s,%d,%d,%d,%d,%s,%d,%d,%d,%d,%d,%s,%s,%s,%d,%d",
		this->owner.c_str(),
		this->buildingType.c_str(),
		this->health,
		this->MapCoords.X,
		this->MapCoords.Y,
		this->direction,
		this->tag.c_str(),
		this->sellable != 0,
		this->aiRepair != 0,
		this->powered != 0,
		this->powerupCount,
		this->spotlight,
		this->powerupOne.c_str(),
		this->powerupTwo.c_str(),
		this->powerupThree.c_str(),
		this->rebuild != 0,
		this->showName != 0
		);

	return buffer;
}
