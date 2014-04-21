#include "stdafx.h"
#include "WeaponType.hpp"
#include "../../Log.hpp"
#include "../General/EntryHelper.hpp"
#include "ProjectileType.hpp"
#include "WarheadType.hpp"
#include "Animation.hpp"

/* static */ List<WeaponType> WeaponType::Array;

WeaponType::WeaponType(const std::string& id)
:AbstractType(id)
{
}

void WeaponType::loadRules(INIFile* rules)
{
	INISection* rulesSection = rules->getSection(ID);
	if (!rulesSection) return;

	AbstractType::loadRules(rules);

	Projectile = rulesSection->readStringValue("Projectile", Projectile);
	ProjectileType::Array.findOrAllocate(Projectile);
	WarheadType::Array.findOrAllocate(rulesSection->readStringValue("Warhead"));
	allocateList(Animation::Array, rulesSection->readStringValue("Anim"));
}

void WeaponType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	AbstractType::loadArt(art);
}