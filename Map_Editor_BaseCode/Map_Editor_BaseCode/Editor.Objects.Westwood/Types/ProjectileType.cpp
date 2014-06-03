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
	rulesSection->readStringValue("Image", Image, ID.c_str());
	rulesSection->readStringValue("AirburstWeapon", AirburstWeapon);
	rulesSection->readStringValue("ShrapnelWeapon", ShrapnelWeapon);

	WeaponType::Array.findOrAllocate(AirburstWeapon);
	WeaponType::Array.findOrAllocate(ShrapnelWeapon);
}

void ProjectileType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(Image);
	if (!artSection) return;

	AbstractType::loadArt(art);
	artSection->readStringValue("Trailer", Trailer);
	Animation::Array.findOrAllocate(Trailer);
}
