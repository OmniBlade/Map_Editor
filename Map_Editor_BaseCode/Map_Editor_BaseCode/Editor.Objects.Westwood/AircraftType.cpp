#include "stdafx.h"
#include "AircraftType.hpp"


AircraftType::AircraftType(INISection* _rulesSection, INISection* _artSection)
:TechnoType(_rulesSection, _artSection), artSection(_artSection), rulesSection(_rulesSection)
{
}

void AircraftType::loadRules()
{
	Fighter = rulesSection->readBoolValue("Fighter", false);
	CarryAll = rulesSection->readBoolValue("CarryAll", false);
}

void AircraftType::loadArt()
{

}
