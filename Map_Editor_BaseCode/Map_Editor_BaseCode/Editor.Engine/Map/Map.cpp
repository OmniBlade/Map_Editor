#include "stdafx.h"
#include "Map.hpp"

/* static */ Map* Map::theMap;
/* static */ Map* Map::getInstance()
{
	if (theMap)
	{
		return theMap;
	}
	else
	{
		theMap = new Map();
		return theMap;
	}
}

Map::Map()
{

}

void Map::writeAll()
{

}