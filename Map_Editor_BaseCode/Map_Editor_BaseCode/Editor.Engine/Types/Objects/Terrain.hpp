#pragma once

#include "../Managers/MapObjectList.hpp"
#include <string>
#include "../../../Editor.Objects.Westwood/Vector2D.hpp"

class TerrainType;
class INIFile;

class Terrain
{
public:
	static MapObjectList<Terrain> Array;
	static void writeToINI(INIFile& file);

	Terrain();
	void parse(const std::string& index, const std::string& list);
	std::string asString();


	std::string Location, terrainType;

	Vector2D loc;
	TerrainType* pTerrainType;
};

