#include "stdafx.h"
#include "Terrain.hpp"
#include "../../../Editor.Objects.Westwood/Types/TerrainType.hpp"
#include "../../../Log.hpp"
#include <cstdlib>

/* static */ ObjectList<Terrain> Terrain::Array;

Terrain::Terrain()
{
}

void Terrain::parse(const std::string& index, const std::string& list)
{
	Location = index;
	loc.x = atoi(Location.substr(Location.length() - 3, Location.length()).c_str());
	loc.y = atoi(Location.substr(0, Location.length() - 3).c_str());

	terrainType = list;
	pTerrainType = TerrainType::Array.find(terrainType);
}
