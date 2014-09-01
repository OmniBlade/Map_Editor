#pragma once

#include "../Managers/MapObjectList.hpp"
#include <string>
#include "../../../Editor.Objects.Westwood/Vector2D.hpp"

class BuildingType;
class Tag;
class Country;
class House;

class Structure
{
public:
	static MapObjectList<Structure> Array;

	Structure();

	void parse(const std::string& index, const std::string& list);

	/*
	Returns the Structure as a string, ready to paste in a map
	@return The string like it appears in a map file
	*/
	std::string asString() const;

	/*

	*/
	void setBuildingType();

	std::string owner = "";
	Country* pCountry;
	House* pHouse;
	std::string buildingType = "";
	BuildingType* pBuilding = nullptr;
	unsigned int health = 256;
	Vector2D loc;
	unsigned int direction = 0;
	std::string tag = "None";
	Tag* pTag;
	bool sellable = true;
	bool aiRepair = false;
	bool powered = true;
	int powerupCount;
	unsigned int spotlight = 0;
	std::string powerupOne = "None";
	std::string powerupTwo = powerupOne;
	std::string powerupThree = powerupOne;
	bool rebuild = false; // Doesn't work anyway
	bool showName = false; // Doesn't work for RA2/YR, only TS!
};

