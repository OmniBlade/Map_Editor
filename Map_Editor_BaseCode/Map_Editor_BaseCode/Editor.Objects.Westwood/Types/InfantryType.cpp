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

	OccupyWeapon = rulesSection->readStringValue("OccupyWeapon", OccupyWeapon);
	EliteOccupyWeapon = rulesSection->readStringValue("EliteOccupyWeapon", EliteOccupyWeapon);

	if (OccupyWeapon != "")
		WeaponType::Array.findOrAllocate(OccupyWeapon);
	if (EliteOccupyWeapon != "")
		WeaponType::Array.findOrAllocate(EliteOccupyWeapon);
	
	Cyborg = rulesSection->readBoolValue("Cyborg", Cyborg);
	NotHuman = rulesSection->readBoolValue("NotHuman", NotHuman);
	Occupier = rulesSection->readBoolValue("Occupier", Occupier);
	Civilian = rulesSection->readBoolValue("Civilian", Civilian);
}

void InfantryType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	TechnoType::loadArt(art);

}