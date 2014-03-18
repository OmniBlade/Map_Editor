#include "stdafx.h"
#include "Map.hpp"


Map::Map(INIManager* _iniHandler, TheaterCollection* _theaterColl)
:theaterColl(_theaterColl), iniHandler(_iniHandler)
{
}

Map::~Map()
{
}

void Map::loadTheater(const std::string& _theaterName)
{


}