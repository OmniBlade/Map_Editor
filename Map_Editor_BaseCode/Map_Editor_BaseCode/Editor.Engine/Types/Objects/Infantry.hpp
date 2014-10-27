#pragma once

#include "../Managers/MapObjectList.hpp"
#include <string>
#include "Object.h"

class InfantryType;
class Tag;
class House;
class Country;
class INIFile;

class Infantry : public Object
{
public:
	static MapObjectList<Infantry> Array;
	static void writeToINI(INIFile& file);
	Infantry();

	void parse(const std::string& index, const std::string& list);

	/*
	Returns the Infantry as a string, ready to paste in a map
	@return The string like it appears in a map file
	*/
	std::string asString() const;

	std::string owner = "";
	Country* pCountry;
	House* pHouse;
	std::string infantryType = "";
	unsigned int health = 256;
	unsigned int subCell = 0;
	std::string mission = "Guard";
	unsigned int direction = 64;
	std::string tag = "None";
	Tag* pTag;
	unsigned int veterancy = 0;
	int group = -1;
	bool onBridge = false;
	bool recruitable = true;
	bool aiRecruitable = false;
};

