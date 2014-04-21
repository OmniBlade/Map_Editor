#pragma once

#include <string>
#include "../../Editor.Objects.Westwood/Vector2D.hpp"

class Infantry
{
public:
	Infantry();

	/*
	Returns the Infantry as a string, ready to paste in a map
	@return The string like it appears in a map file
	*/
	std::string asString() const;

	std::string owner = "";
	std::string infantryType = "";
	unsigned int health = 256;
	Vector2D loc;
	unsigned int subCell = 0;
	std::string mission = "Guard";
	unsigned int direction = 64;
	std::string tag = "none";
	unsigned int veterancy = 0;
	int group = -1;
	bool onBridge = false;
	bool recruitable = true;
	bool aiRecruitable = false;
};

