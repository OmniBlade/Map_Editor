#include "stdafx.h"
#include "ProjectileType.hpp"
#include "WeaponType.hpp"
#include "../../Log.hpp"
#include "Animation.hpp"

/* static */ List<ProjectileType> ProjectileType::Array;

ProjectileType::ProjectileType(const std::string& id)
:AbstractType(id)
{

}

void ProjectileType::loadRules(INIFile* rules)
{
	INISection* rulesSection = rules->getSection(ID);
	if (!rulesSection) return;

	AbstractType::loadRules(rules);
	Image = rulesSection->readStringValue("Image", ID);
	AirburstWeapon = rulesSection->readStringValue("AirburstWeapon", AirburstWeapon);
	ShrapnelWeapon = rulesSection->readStringValue("ShrapnelWeapon", ShrapnelWeapon);

	if (AirburstWeapon != "")
		WeaponType::Array.findOrAllocate(AirburstWeapon);
	if (ShrapnelWeapon != "")
		WeaponType::Array.findOrAllocate(ShrapnelWeapon);
}

void ProjectileType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(Image);
	if (!artSection) return;

	AbstractType::loadArt(art);
	Animation::Array.findOrAllocate(artSection->readStringValue("Trailer"));
}
