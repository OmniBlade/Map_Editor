#pragma once
#include <string>

class AircraftType;
class VehicleType;
class InfantryType;

class TFEntry
{
public:
	TFEntry(const std::string& list);

	int count;
	std::string unit;

	AircraftType* aircraft;
	VehicleType* vehicle;
	InfantryType* infantry;

};

