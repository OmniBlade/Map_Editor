#pragma once

#include <string>

class TechType
{
public:
	TechType();
	~TechType();

	/*
		All the properties that are used by all types
		Please note: I decided to list all the flags like they are in the INI
	*/
	//RULES FLAGS
	std::string Name;
	std::string UIName;
	std::string Image;
	int TechLevel; // Used to tell the user what unit can and cannot be build (threshold 1 - 10?)
	int AIBasePlanningSide; // Most def needed with Ares
	int Passengers;				// Isn't this only used by Aircraft and Vehicles?
	float Weight;				// Something about passengers
	float PhysicalSize;			// This too
	float Size;					// This too, related to tag below
	float SizeLimit;			// Largest type of unit allowed?

	
	//bool ConsideredAircraft; // This could be useful for something, until it is leave it commented out
	
	bool IsTrain; // This should be used for 'Follows ID' on trains and wagons


};

