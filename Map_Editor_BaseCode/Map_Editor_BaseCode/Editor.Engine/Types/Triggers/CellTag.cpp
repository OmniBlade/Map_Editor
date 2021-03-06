#include "stdafx.h"
#include "CellTag.hpp"
#include "Tag.hpp"
#include "../../../Log.hpp"
#include <cstdlib>
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"

/* static */ MapObjectList<CellTag> CellTag::Array;

CellTag::CellTag()
{
}

void CellTag::parse(const std::string& location, const std::string& tag)
{
	Location = location;
	pTag = Tag::Array.find(tag);
	MapCoords.X = atoi(Location.substr(Location.length() - 3, Location.length()).c_str());
	MapCoords.Y = atoi(Location.substr(0, Location.length() - 3).c_str());
}

void CellTag::writeToINI(INIFile& file)
{
	if (Array.objectList.size() == 0)
	{
		Log::line("SECTION - CellTags does not exist, will not write to map.", Log::DEBUG);
		return;
	}

	for (auto& it : Array.objectList)
	{
		if (it->pTag)
		{
			file.SetValue("CellTags", it->MapCoords.asString(), it->pTag->ID);
		}
	}
}