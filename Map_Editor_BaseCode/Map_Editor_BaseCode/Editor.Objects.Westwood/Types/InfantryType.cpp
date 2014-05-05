#include "stdafx.h"
#include "InfantryType.hpp"
#include "../../Log.hpp"
#include "WeaponType.hpp"

/* static */ List<InfantryType> InfantryType::Array;

InfantryType::InfantryType(const std::string& id)
:TechnoType(id)
{
}

void InfantryType::loadRules(INIFile* rules)
{

	INISection* rulesSection = rules->getSection(ID);
	if (!rulesSection) return;

	TechnoType::loadRules(rules);

	rulesSection->readStringValue("OccupyWeapon", OccupyWeapon);
	rulesSection->readStringValue("EliteOccupyWeapon", EliteOccupyWeapon);

	WeaponType::Array.findOrAllocate(OccupyWeapon);
	WeaponType::Array.findOrAllocate(EliteOccupyWeapon);
	
	rulesSection->readBoolValue("Cyborg", Cyborg);
	rulesSection->readBoolValue("NotHuman", NotHuman);
	rulesSection->readBoolValue("Occupier", Occupier);
	rulesSection->readBoolValue("Civilian", Civilian);
}

void InfantryType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	TechnoType::loadArt(art);

}