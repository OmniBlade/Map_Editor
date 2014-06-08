#pragma once

#include "../Managers/ObjectList.hpp"
#include <string>

class TeamType;
class VehicleType;
class InfantryType;
class BuildingType;
class AircraftType;
class Country;

class AITriggerType
{
public:
	static ObjectList<AITriggerType> Array;

	AITriggerType();
	void parse(const std::string& id, const std::string& list, bool isGlobal_ = false);
	std::string asString();
	std::string createParameters();

	std::string ID, name, owner, techType, uselessString, parameterString, tt1, tt2;
	int techlevel, aiTriggerType, unknown, side, paramNumber, paramEquation;
	float weight, minWeight, maxWeight;
	bool baseDefense, skirmish, easy, medium, hard;
	TeamType* teamtype1 = nullptr;
	TeamType* teamtype2 = nullptr;
	VehicleType* pVehicleType;
	InfantryType* pInfantryType;
	BuildingType* pBuildingType;
	AircraftType* pAircraftType;
	Country* pCountry;
	bool isGlobal;
};

