#include "stdafx.h"
#include "InfantryType.hpp"


InfantryType::InfantryType(INISection* _rulesSection, INISection* _artSection)
:TechnoType(_rulesSection, _artSection), artSection(_artSection), rulesSection(_rulesSection)
{
}

void InfantryType::loadRules()
{
	Cyborg = rulesSection->readBoolValue("Cyborg", false);
	NotHuman = rulesSection->readBoolValue("NotHuman", false);
	Occupier = rulesSection->readBoolValue("Occupier", false);
	Civilian = rulesSection->readBoolValue("Civilian", false);
}

void InfantryType::loadArt()
{

}