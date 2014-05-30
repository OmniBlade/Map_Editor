#pragma once

#include "../Managers/ObjectList.hpp"
#include <string>
#include "../../../Editor.Objects.Westwood/Vector2D.hpp"
#include "../../../Editor.Objects.Westwood/Types/VehicleType.hpp"

class Unit
{
public:
	static ObjectList<Unit> Array;

	Unit();

	void parse(const std::string& index, const std::string& list);

	/*
	Returns the Unit as a string, ready to paste in a map
	@return The string like it appears in a map file
	*/
	std::string asString() const;

	/*
	
	*/
	void setVehicleType();

	std::string owner = "";
	std::string vehicleType = "";
	VehicleType* pVehicle = nullptr;
	unsigned int health = 256;
	Vector2D loc;
	unsigned int direction = 64;
	std::string mission = "Guard";
	std::string tag = "none";
	int veterancy = 0;
	int group = -1;
	bool onBridge = false;
	int followsID = -1;		// This takes an index from UNITS list map, not VEHICLETYPES list from rules
	bool recruitable = true;
	bool aiRecruitable = false;

};

