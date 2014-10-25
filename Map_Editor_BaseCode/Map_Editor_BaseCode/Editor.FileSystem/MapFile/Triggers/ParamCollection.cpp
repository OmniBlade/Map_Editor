#include "stdafx.h"
#include "ParamCollection.hpp"
#include "../../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../../Log.hpp"
#include <string>

ParamCollection::ParamCollection()
{
	parse();
	applySpecialCases();
}

void ParamCollection::parse()
{
	INIFile* file = INIManager::instance()->getRoot("PARAMS");
	INISection* params = file->getSection("ParamTypes");

	std::vector<std::string>& defaults = getDefaultValues();

	for (int i = 0; i < paramCount; ++i)
	{
		if (params->keyExists(Log::toString(i)))
			paramList.push_back(std::make_unique<ParamType>(i, params->getValue(Log::toString(i)), paramCount));
		else
		{
			//Because the list is hardcoded, we can easily insert a missing name
			paramList.push_back(std::make_unique<ParamType>(i, defaults[i], paramCount));
			Log::line("ParamType expected at index " + Log::toString(i) + " is not found, inserting default value.", Log::DEBUG);
		}
	}
}

void ParamCollection::applySpecialCases()
{
	for (unsigned int i = 0; i < paramList.size(); ++i)
	{
		auto it = paramList[i].get();
		switch (paramList[i]->paramID)
		{
		case 0x0E: //TTypes
			it->diffGlobal = true;
			break;
		case 0x34: //STypes
			it->diffGlobal = true;
			break;
		case 0x39: //TForces
			it->diffGlobal = true;
			break;
		}
	}
}

ParamType* ParamCollection::get(int ID)
{
	//if (ID < 0 || ID > 0)
//		return nullptr;

	for (unsigned int i = 0; i < paramList.size(); ++i)
	{
		if (paramList[i]->paramID == ID)
			return paramList[i].get();
	}
	return nullptr;
}

std::vector<std::string> ParamCollection::getDefaultValues()
{
	std::vector<std::string> defaults;

	defaults.push_back("Nothing,0");
	defaults.push_back("AircraftType,1");
	defaults.push_back("Animation,2");
	defaults.push_back("BuildingType,3");
	defaults.push_back("Country,41");
	defaults.push_back("Speech,4");
	defaults.push_back("House,5");
	defaults.push_back("InfantryType,6");
	defaults.push_back("Movie,7");
	defaults.push_back("Particle,8");
	defaults.push_back("Sound,9");
	defaults.push_back("Text String,10");
	defaults.push_back("SuperWeapon,11");
	defaults.push_back("Tag,12");
	defaults.push_back("TeamType,13");
	defaults.push_back("TechnoType,14");
	defaults.push_back("Theme,15");
	defaults.push_back("Trigger,16");
	defaults.push_back("VehicleType,17");
	defaults.push_back("Local variable,18");
	defaults.push_back("Global variable,19");
	defaults.push_back("Waypoint,20");
	defaults.push_back("WeaponType,21");
	defaults.push_back("Activated,22");
	defaults.push_back("Left,0");
	defaults.push_back("Top,0");
	defaults.push_back("Width,0");
	defaults.push_back("Height,0");
	defaults.push_back("Quarry,23");
	defaults.push_back("Seconds,0");
	defaults.push_back("Credits,0");
	defaults.push_back("Group,24");
	defaults.push_back("Speed,25");
	defaults.push_back("Voxel Anim,26");
	defaults.push_back("CrateType,27");
	defaults.push_back("Speech bubble,28");
	defaults.push_back("Light behavior,29");
	defaults.push_back("Event,30");
	defaults.push_back("Size,31");
	defaults.push_back("Number,0");
	defaults.push_back("Frames,0");
	defaults.push_back("Tab,32");
	defaults.push_back("Percentage,0");
	defaults.push_back("Zoom level,33");
	defaults.push_back("Amount,0");
	defaults.push_back("Ambient rate,0");
	defaults.push_back("Value,0");
	defaults.push_back("Lighting level,0");
	defaults.push_back("Ambient step,0");
	defaults.push_back("Ambient level,0");

	//Mostly ScriptTypes actions
	defaults.push_back("Mission,34");
	defaults.push_back("Facing,35");
	defaults.push_back("ScriptType,36");
	defaults.push_back("Split Into,37");
	defaults.push_back("Script Line,38");
	defaults.push_back("Cell,0");
	defaults.push_back("TechLevel,39");
	defaults.push_back("TaskForce,40");
	
	return defaults;
}