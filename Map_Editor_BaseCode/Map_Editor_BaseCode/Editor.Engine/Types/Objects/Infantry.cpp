#include "stdafx.h"
#include "Infantry.hpp"
#include <sstream>
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Editor.Objects.Westwood/Types/InfantryType.hpp"
#include "../../../Editor.Objects.Westwood/Types/Country.hpp"
#include "../Triggers//Tag.hpp"
#include "../House.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"

/* static */ MapObjectList<Infantry> Infantry::Array;

Infantry::Infantry()
{
}

void Infantry::parse(const std::string& index, const std::string& list)
{
	int x, y;
	LineSplitter split(list);
	if (split.pop(owner) && split.pop(infantryType) && split.pop(health) && split.pop(x) && split.pop(y)
		&& split.pop(subCell) && split.pop(mission) && split.pop(direction) && split.pop(tag) && split.pop(veterancy) && split.pop(group)
		&& split.pop(onBridge) && split.pop(recruitable) && split.pop(aiRecruitable))
	{
		MapCoords.X = x;
		MapCoords.Y = y;
		setObjectType(InfantryType::Array.find(infantryType));
		pTag = Tag::Array.find(tag);
		pCountry = Country::Array.find(owner);
		pHouse = House::Array.find(owner);
	}
	else
	{
		Log::line("Unable to parse Infantry with entry number '" + index + "'.", Log::DEBUG);
	}
}

void Infantry::writeToINI(INIFile& file)
{
	if (Array.objectList.size() == 0)
	{
		Log::line("SECTION - Infantry does not exist, will not write to map.", Log::DEBUG);
		return;
	}


	std::stringstream number;
	int i = 0;
	for (auto& it : Array.objectList)
	{
		number << i;
		file.SetValue("Infantry", number.str(), it->asString());
		++i;
		number.str(std::string());
	}
}

std::string Infantry::asString() const
{
	char buffer[512];
	//Don't need to include the ID, so no "%s = "
	sprintf_s(buffer, 512, "%s,%s,%d,%d,%d,%d,%s,%d,%s,%d,%d,%d,%d,%d",
		this->owner.c_str(),
		this->infantryType.c_str(),
		this->health,
		this->MapCoords.X,
		this->MapCoords.Y,
		this->subCell,
		this->mission.c_str(),
		this->direction,
		this->tag.c_str(),
		this->veterancy,
		this->group,
		this->onBridge != 0,
		this->recruitable != 0,
		this->aiRecruitable != 0
		);

	return buffer;
}
