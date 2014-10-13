#include "stdafx.h"
#include "Smudge.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.Objects.Westwood/Types/SmudgeType.hpp"
#include <sstream>

/* static */ MapObjectList<Smudge> Smudge::Array;

Smudge::Smudge()
{

}

void Smudge::parse(const std::string& id, const std::string& list)
{
	LineSplitter split(list);
	if (split.pop(smudge) && split.pop(loc.x) && split.pop(loc.y) && split.pop(unknown))
	{
		pSmudgeType = SmudgeType::Array.find(smudge);
	}
	else
	{
		Log::line("Unable to parse Smudge with index '" + id + "'.", Log::DEBUG);
	}
}

void Smudge::writeToINI(INIFile& file)
{
	if (Array.objectList.size() == 0)
	{
		Log::line("SECTION - Smudge does not exist, will not write to map.", Log::DEBUG);
		return;
	}

	std::stringstream number;
	int i = 0;
	for (auto& it : Array.objectList)
	{
		number << i;
		file.SetValue("Smudge", number.str(), it->asString());
		++i;
		number.str(std::string());
	}
}

std::string Smudge::asString()
{
	char buffer[512];
	sprintf_s(buffer, 512, "%s,%d,%d,%d",
		this->pSmudgeType->ID.c_str(),
		this->loc.x,
		this->loc.y,
		0
		);

	return buffer;

}