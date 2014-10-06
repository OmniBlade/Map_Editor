#pragma once

#include <string>
#include "../../Editor.Objects.Westwood/Vector2D.hpp"

class BaseNode
{
public:
	BaseNode(const std::string& buildingType_, int x, int y);

	std::string asString();

	std::string buildingType;
	Vector2D loc;
};

