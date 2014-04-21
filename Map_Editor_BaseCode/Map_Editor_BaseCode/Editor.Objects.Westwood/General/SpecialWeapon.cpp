#include "stdafx.h"
#include "SpecialWeapon.hpp"
#include "EntryHelper.hpp"
#include "../Types/ProjectileType.hpp"
#include "../Types/WarheadType.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"

SpecialWeapon::SpecialWeapon()
{
}

void SpecialWeapon::loadRules(INIFile* file)
{
	INISection* section = file->getSection("SpecialWeapons");
	if (!section) return;

	allocateList(WarheadType::Array, section->readStringValue("NukeWarhead"));
	allocateList(ProjectileType::Array, section->readStringValue("NukeProjectile"));
	allocateList(ProjectileType::Array, section->readStringValue("NukeDown"));
	allocateList(WarheadType::Array, section->readStringValue("MutateWarhead"));
	allocateList(WarheadType::Array, section->readStringValue("MutateExplosionWarhead"));
	allocateList(WarheadType::Array, section->readStringValue("EMPulseWarhead"));
	allocateList(ProjectileType::Array, section->readStringValue("EMPulseProjectile"));
}