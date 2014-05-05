#include "stdafx.h"
#include "Terrain.hpp"
#include "../../../Editor.Objects.Westwood/Types/TerrainType.hpp"
#include "../../../Log.hpp"
#include <cstdlib>

Terrain::Terrain(const std::string& location, const std::string& type)
:Location(location), Type(type)
{
	parse();
}

void Terrain::parse()
{
	Log::note("Types of TerrainType aren't parsed yet!", Log::DEBUG);
	loc.x = atoi(Location.substr(Location.length() - 3, Location.length()).c_str());
	loc.y = atoi(Location.substr(0, Location.length() - 3).c_str());
}
