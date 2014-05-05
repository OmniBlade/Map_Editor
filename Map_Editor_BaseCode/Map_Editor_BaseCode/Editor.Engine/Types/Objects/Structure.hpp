#pragma once

#include <string>
#include "../../../Editor.Objects.Westwood/Vector2D.hpp"
#include "../../../Editor.Objects.Westwood/Types/BuildingType.hpp"

class Structure
{
public:
	Structure();

	/*
	Returns the Structure as a string, ready to paste in a map
	@return The string like it appears in a map file
	*/
	std::string asString() const;

	/*

	*/
	void setBuildingType();

	std::string owner = "";
	std::string buildingType = "";
	BuildingType* pBuilding = nullptr;
	unsigned int health = 256;
	Vector2D loc;
	unsigned int direction = 0;
	std::string tag = "none";
	bool sellable = true;
	bool aiRepair = false;
	bool powered = true;
	unsigned int powerupCount = 0;
	unsigned int spotlight = 0;
	std::string powerupOne = "none";
	std::string powerupTwo = powerupOne;
	std::string powerupThree = powerupOne;
	bool rebuild = false; // Doesn't work anyway
	bool showName = false; // Doesn't work for RA2/YR, only TS!
};

