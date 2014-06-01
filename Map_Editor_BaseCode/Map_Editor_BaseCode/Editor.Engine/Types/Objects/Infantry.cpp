#include "stdafx.h"
#include "Infantry.hpp"
#include <sstream>
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Editor.Objects.Westwood/Types/InfantryType.hpp"
#include "../Triggers//Tag.hpp"

/* static */ ObjectList<Infantry> Infantry::Array;

Infantry::Infantry()
{
}

void Infantry::parse(const std::string& index, const std::string& list)
{
	LineSplitter split(list);
	if (split.pop(owner) && split.pop(infantryType) && split.pop(health) && split.pop(loc.x) && split.pop(loc.y)
		&& split.pop(subCell) && split.pop(mission) && split.pop(direction) && split.pop(tag) && split.pop(veterancy) && split.pop(group)
		&& split.pop(onBridge) && split.pop(recruitable) && split.pop(aiRecruitable))
	{
		pInfantry = InfantryType::Array.find(infantryType);
		pTag = Tag::Array.find(tag);
	}
	else
	{
		Log::note("Unable to parse Infantry with entry number '" + index + "'.", Log::DEBUG);
	}
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