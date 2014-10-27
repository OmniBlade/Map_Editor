#pragma once

#include "../Managers/MapObjectList.hpp"
#include <string>
#include "Object.h"

class Tag;
class VehicleType;
class Country;
class House;
class INIFile;

class Unit : public Object
{
public:
	static MapObjectList<Unit> Array;
	static void writeToINI(INIFile& file);

	Unit();

	void parse(const std::string& index, const std::string& list);

	/*
	Returns the Unit as a string, ready to paste in a map
	@return The string like it appears in a map file
	*/
	std::string asString() const;

	std::string owner = "";
	Country* pCountry;
	House* pHouse;
	std::string vehicleType = "";
	unsigned int health = 256;
	unsigned int direction = 64;
	std::string mission = "Guard";
	std::string tag = "None";
	Tag* pTag;
	int veterancy = 0;
	int group = -1;
	bool onBridge = false;
	int followsID = -1;		// This takes an index from UNITS list map, not VEHICLETYPES list from rules
	bool recruitable = true;
	bool aiRecruitable = false;

};

