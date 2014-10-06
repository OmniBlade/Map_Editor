#include "stdafx.h"
#include "Smudge.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../Editor.Objects.Westwood/Types/SmudgeType.hpp"

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