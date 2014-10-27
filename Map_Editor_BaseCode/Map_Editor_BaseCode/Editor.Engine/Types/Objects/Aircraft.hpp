#pragma once

#include "../Managers/MapObjectList.hpp"
#include "Object.h"
#include <string>

class AircraftType;
class Tag;
class House;
class Country;
class INIFile;

class Aircraft : public Object
{
public:
	static MapObjectList<Aircraft> Array;
	static void writeToINI(INIFile& file);

	Aircraft();
	
	void parse(const std::string& index, const std::string& list);

	/*
	Returns the Aircraft as a string, ready to paste in a map
	@return The string like it appears in a map file
	*/
	std::string asString() const;

	std::string owner = "";
	Country* pCountry;
	House* pHouse;
	std::string aircraftType = "";
	unsigned int health = 256;
	unsigned int direction = 64;
	std::string mission = "Guard";
	std::string tag = "None";
	Tag* pTag;
	int veterancy = 0;
	int group = -1;
	bool recruitable = true;
	bool aiRecruitable = false;
};

