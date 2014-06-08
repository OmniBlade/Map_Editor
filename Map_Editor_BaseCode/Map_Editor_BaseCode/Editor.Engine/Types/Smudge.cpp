#include "stdafx.h"
#include "Smudge.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../Editor.Objects.Westwood/Types/SmudgeType.hpp"

/* static */ ObjectList<Smudge> Smudge::Array;

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
		Log::note("Unable to parse Smudge with index '" + id + "'.", Log::DEBUG);
	}
}