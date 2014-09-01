#pragma once

#include "../Managers/MapObjectList.hpp"
#include <string>
#include "../../../Editor.Objects.Westwood/Vector2D.hpp"

class TerrainType;

class Terrain
{
public:
	static MapObjectList<Terrain> Array;

	Terrain();
	void parse(const std::string& index, const std::string& list);

	std::string Location, terrainType;

	Vector2D loc;
	TerrainType* pTerrainType;
};

