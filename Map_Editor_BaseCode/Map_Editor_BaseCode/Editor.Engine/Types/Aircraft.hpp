#pragma once

#include <string>
#include "../../Editor.Objects.Westwood/Vector2D.hpp"

class Aircraft
{
public:
	Aircraft();
	
	/*
	Returns the Aircraft as a string, ready to paste in a map
	@return The string like it appears in a map file
	*/
	std::string asString() const;

	std::string owner = "";
	std::string aircraftType = "";
	unsigned int health = 256;
	Vector2D loc;
	unsigned int direction = 64;
	std::string mission = "Guard";
	std::string tag = "none";
	int veterancy = 0;
	int group = -1;
	bool recruitable = true;
	bool aiRecruitable = false;
};

