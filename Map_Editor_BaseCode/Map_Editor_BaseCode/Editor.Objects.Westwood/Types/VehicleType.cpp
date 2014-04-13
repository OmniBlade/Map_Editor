#include "stdafx.h"
#include "VehicleType.hpp"


VehicleType::VehicleType(INISection* _rulesSection, INISection* _artSection)
:TechnoType(_rulesSection, _artSection), artSection(_artSection), rulesSection(_rulesSection)
{
}

void VehicleType::loadRules()
{
	Harvester = rulesSection->readBoolValue("Harvester", false);
	Weeder = rulesSection->readBoolValue("Weeder", false);
	UseTurretShadow = rulesSection->readBoolValue("UseTurretShadow", false);
}

void VehicleType::loadArt()
{
	StandingFrames = artSection->readIntValue("StandingFrames", 0);
	Facings = artSection->readIntValue("Facings", 8);

}