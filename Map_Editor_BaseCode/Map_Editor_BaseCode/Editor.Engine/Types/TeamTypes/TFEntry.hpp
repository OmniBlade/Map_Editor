#pragma once
#include <string>

class AircraftType;
class VehicleType;
class InfantryType;

class TFEntry
{
public:
	TFEntry(const std::string& list);
	std::string asString();

	int count;
	std::string unit;

	AircraftType* aircraft;
	VehicleType* vehicle;
	InfantryType* infantry;

};

