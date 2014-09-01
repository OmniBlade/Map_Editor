#include "stdafx.h"
#include "ParamContent.hpp"

ParamContent::ParamContent()
{
}

/*
	A very, very, VERY trial-ish implementation of getting a ParamType's list

	Basically, this function will tie shit that belongs to a ParamType to actual content.
	For example, 1 = AircraftType, a full list of AircraftTypes will be returned to fill the dropdown box in the UI.
	
	Again, a trial-ish implementation and I wouldn't be surprised if shit goes wild when the UI is added
*/
std::vector<std::string> ParamContent::get(int paramID, bool isForScript /* = false */)
{
	std::vector<std::string> paramContent;

	/* 
		I'm not entirely sure, but for ParamTypes that don't require a specific list 
		you should not even bother to fill it...
	*/
	switch (paramID)
	{
	case 29:
	case 30:
	case 39:
	case 40:
	case 42:
	case 44:
	case 55:
		return paramContent;
	}

	fillVector(paramContent, paramID);

	return paramContent;
}

/*
	
*/
void ParamContent::fillVector(std::vector<std::string>& paramVector, int paramID)
{
	switch (paramID)
	{
	case 1: //AircraftType
		break;
	case 2: //Animation
		break;
	case 3: ///BuildingType
		break;
	case 4: //Building TechnoType
		break;
	case 5: //Speech
		break;
	case 6: //House
		break;
	case 7: //InfantryType
		break;
	case 8: //Movie
		break;
	case 9: //Particle
		break;
	case 10: //Sound
		break;
	case 11: //CSF-String
		break;
	case 12: //SuperWeapon
		break;
	case 13: //Tag
		break;
	case 14: //TeamType
		break;
	case 15: //TechnoType
		break;
	case 16: //Theme
		break;
	case 17: //Trigger
		break;
	case 18: //VehicleType
		break;
	case 19: //Local Variable
		break;
	case 20: //Global Variable
		break;
	case 21: //Waypoint INDEX
		break;
	case 22: //WeaponType
		break;
	case 23: //Activated
		paramVector.push_back("0 - No");
		paramVector.push_back("1 - Yes");
		break;
	case 24: //Left
		break;
	case 25: //Top
		break;
	case 26: //Width
		break;
	case 27: //Height
		break;
	case 28: //Quarry
		break;
	case 31: //Group
		break;
	case 32: //Speed
		paramVector.push_back("0 - Slowest");
		paramVector.push_back("1 - Slow");
		paramVector.push_back("2 - Normal");
		paramVector.push_back("3 - Fast");
		paramVector.push_back("4 - Fastest");
		break;

	}
}