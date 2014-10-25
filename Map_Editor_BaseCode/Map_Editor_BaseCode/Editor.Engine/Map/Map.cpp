#include "stdafx.h"
#include "Map.hpp"
#include "../Basics/MapStats.hpp"

/* static */ Map* Map::pInstance;
/* static */ Map* Map::instance()
{
	if (pInstance)
	{
		return pInstance;
	}
	else
	{
		pInstance = new Map();
		return pInstance;
	}
}

Map::Map()
{

}

void Map::setupCells()
{
	auto pMapStats = MapStats::instance();
	cells.resize(pMapStats->Size.Width * pMapStats->Size.Height);

}