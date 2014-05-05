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

	rulesSection->readStringValue("Projectile", Projectile);
	rulesSection->readStringValue("Warhead", Warhead);
	rulesSection->readStringValue("Anim", Anim);

	ProjectileType::Array.findOrAllocate(Projectile);
	WarheadType::Array.findOrAllocate(Warhead);
	allocateList(Animation::Array, Anim);
}

void WeaponType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	AbstractType::loadArt(art);
}