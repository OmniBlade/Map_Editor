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

	NukeWarhead;
	NukeProjectile;
	NukeDown;
	MutateWarhead;
	MutateExplosionWarhead;
	EMPulseWarhead;
	EMPulseProjectile;

	section->readStringValue("NukeWarhead", NukeWarhead);
	section->readStringValue("NukeProjectile", NukeProjectile);
	section->readStringValue("NukeDown", NukeDown);
	section->readStringValue("MutateWarhead", MutateWarhead);
	section->readStringValue("MutateExplosionWarhead", MutateExplosionWarhead);
	section->readStringValue("EMPulseWarhead", EMPulseWarhead);
	section->readStringValue("EMPulseProjectile", EMPulseProjectile);

	WarheadType::Array.findOrAllocate(NukeWarhead);
	ProjectileType::Array.findOrAllocate(NukeProjectile);
	ProjectileType::Array.findOrAllocate(NukeDown);
	WarheadType::Array.findOrAllocate(MutateWarhead);
	WarheadType::Array.findOrAllocate(MutateExplosionWarhead);
	WarheadType::Array.findOrAllocate(EMPulseWarhead);
	ProjectileType::Array.findOrAllocate(EMPulseProjectile);
}