#include "stdafx.h"
#include "Terrain.hpp"
#include "../../../Editor.Objects.Westwood/Types/TerrainType.hpp"
#include "../../../Log.hpp"
#include <cstdlib>
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"

/* static */ MapObjectList<Terrain> Terrain::Array;

Terrain::Terrain()
{
}

void Terrain::parse(const std::string& index, const std::string& list)
{
	Location = index;
	int x = atoi(Location.substr(Location.length() - 3, Location.length()).c_str());
	int y = atoi(Location.substr(0, Location.length() - 3).c_str());

	MapCoords.X = x;
	MapCoords.Y = y;
	terrainType = list;
	setObjectType(TerrainType::Array.find(terrainType));
}

void Terrain::writeToINI(INIFile& file)
{
	if (Array.objectList.size() == 0)
	{
		Log::line("SECTION - Terrain does not exist, will not write to map.", Log::DEBUG);
		return;
	}

	for (auto& it : Array.objectList)
	{
		if (!it->terrainType.empty())
		{
			file.SetValue("Terrain", it->MapCoords.asString(), it->asString());
		}
	}
}

std::string Terrain::asString()
{
	return terrainType;
}
