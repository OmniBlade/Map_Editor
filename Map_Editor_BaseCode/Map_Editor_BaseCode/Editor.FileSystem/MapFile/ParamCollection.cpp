#include "stdafx.h"
#include "ParamCollection.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Log.hpp"
#include <string>

ParamCollection::ParamCollection()
{
	parse();
	applySpecialCases();
}

void ParamCollection::parse()
{
	INIFile* file = INIManager::getManager()->getRoot("PARAMS");
	INISection* params = file->getSection("ParamTypes");

	std::vector<std::string>& defaults = getDefaultValues();

	for (int i = 1; i < paramCount; ++i)
	{
		if (params->checkKeyExistance(Log::toString(i)))
			paramList.push_back(std::make_unique<ParamType>(i, params->getValue(Log::toString(i))));
		else
		{
			//Because the list is hardcoded, we can easily insert a missing name
			paramList.push_back(std::make_unique<ParamType>(i, defaults[i]));
			Log::line("ParamType expected at index " + Log::toString(i) + " is not found, inserting default value.", Log::DEBUG);
		}
	}
}

void ParamCollection::applySpecialCases()
{
	for (unsigned int i = 0; i < paramList.size(); ++i)
	{
		if (paramList[i]->paramID == 14)	  // TeamTypes (diff global AI and local AI)
			paramList[i]->diffGlobal = true;
		else if (paramList[i]->paramID == 52) // ScriptTypes (diff global AI and local AI)
			paramList[i]->diffGlobal = true;
		else if (paramList[i]->paramID == 57) // TaskForces (diff global AI and local AI)
			paramList[i]->diffGlobal = true;
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

	defaults.push_back("AircraftType");
	defaults.push_back("Animation");
	defaults.push_back("BuildingType");
	defaults.push_back("Building TechnoType");
	defaults.push_back("Speech");
	defaults.push_back("House");
	defaults.push_back("Movie");
	defaults.push_back("Particle");
	defaults.push_back("Sound");
	defaults.push_back("Text String");
	defaults.push_back("SuperWeapon");
	defaults.push_back("Tag");
	defaults.push_back("TeamType");
	defaults.push_back("TechnoType");
	defaults.push_back("Theme");
	defaults.push_back("Trigger");
	defaults.push_back("VehicleType");
	defaults.push_back("Local variable");
	defaults.push_back("Global variable");
	defaults.push_back("Waypoint");
	defaults.push_back("WeaponType");
	defaults.push_back("Activated");
	defaults.push_back("Left");
	defaults.push_back("Top");
	defaults.push_back("Height");
	defaults.push_back("Quarry");
	defaults.push_back("Seconds");
	defaults.push_back("Credits");
	defaults.push_back("Group");
	defaults.push_back("Speed");
	defaults.push_back("Voxel Anim");
	defaults.push_back("CrateType");
	defaults.push_back("Speech bubble");
	defaults.push_back("Light behavior");
	defaults.push_back("Event");
	defaults.push_back("Shower");
	defaults.push_back("Number");
	defaults.push_back("Frames");
	defaults.push_back("Tab");
	defaults.push_back("Percentage");
	defaults.push_back("Zoom level");
	defaults.push_back("Amount");
	defaults.push_back("Ambient rate");
	defaults.push_back("Retint value");
	defaults.push_back("Lighting level");
	defaults.push_back("Ambient step");
	defaults.push_back("Ambient level");

	//Mostly ScriptTypes actions
	defaults.push_back("Mission");
	defaults.push_back("Facing");
	defaults.push_back("ScriptType");
	defaults.push_back("Split Into");
	defaults.push_back("Script Line");
	defaults.push_back("Cell");
	defaults.push_back("TechLevel");
	defaults.push_back("TaskForce");
	
	return defaults;
}