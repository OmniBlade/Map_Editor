#pragma once

#include <string>
#include "../../../Editor.Objects.Westwood/Vector2D.hpp"

class TerrainType;

class Terrain
{
public:
	Terrain(const std::string& location, const std::string& type);
	void parse();

	std::string Location, Type;

	Vector2D loc;
	TerrainType* terrainType;
};

