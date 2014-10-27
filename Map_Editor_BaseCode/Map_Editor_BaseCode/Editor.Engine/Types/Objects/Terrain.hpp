#pragma once

#include "../Managers/MapObjectList.hpp"
#include <string>
#include "Object.h"

class TerrainType;
class INIFile;

class Terrain : public Object
{
public:
	static MapObjectList<Terrain> Array;
	static void writeToINI(INIFile& file);

	Terrain();
	void parse(const std::string& index, const std::string& list);
	std::string asString();


	std::string Location, terrainType;
};

