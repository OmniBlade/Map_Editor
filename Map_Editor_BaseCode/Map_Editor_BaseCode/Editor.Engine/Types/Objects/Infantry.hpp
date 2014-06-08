#pragma once

#include "../Managers/ObjectList.hpp"
#include <string>
#include "../../../Editor.Objects.Westwood/Vector2D.hpp"

class InfantryType;
class Tag;
class House;
class Country;

class Infantry
{
public:
	static ObjectList<Infantry> Array;
	Infantry();

	void parse(const std::string& index, const std::string& list);

	/*
	Returns the Infantry as a string, ready to paste in a map
	@return The string like it appears in a map file
	*/
	std::string asString() const;

	/*

	*/
	void setInfantryType();

	std::string owner = "";
	Country* pCountry;
	House* pHouse;
	std::string infantryType = "";
	InfantryType* pInfantry = nullptr;
	unsigned int health = 256;
	Vector2D loc;
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

