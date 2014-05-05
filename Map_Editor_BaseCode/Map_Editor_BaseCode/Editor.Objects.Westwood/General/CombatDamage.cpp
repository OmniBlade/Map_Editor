#include "stdafx.h"
#include "CombatDamage.hpp"
#include "../Types/Animation.hpp"
#include "../Types/WarheadType.hpp"
#include "../Types/WeaponType.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "EntryHelper.hpp"

CombatDamage::CombatDamage()
{

}

void CombatDamage::loadRules(INIFile* file)
{
	INISection* section = file->getSection("CombatDamage");
	if (!section) return;

	section->readStringValue("SplashList", SplashList);
	section->readStringValue("FlameDamage", FlameDamage);
	section->readStringValue("FlameDamage2", FlameDamage2);
	section->readStringValue("C4Warhead", C4Warhead);
	section->readStringValue("CrushWarhead", CrushWarhead);
	section->readStringValue("V3Warhead", V3Warhead);
	section->readStringValue("DMislWarhead", DMislWarhead);
	section->readStringValue("V3EliteWarhead", V3EliteWarhead);
	section->readStringValue("DMislEliteWarhead", DMislEliteWarhead);
	section->readStringValue("CMislWarhead", CMislWarhead);
	section->readStringValue("CMislEliteWarhead", CMislEliteWarhead);
	section->readStringValue("IvanWarhead", IvanWarhead);

	section->readStringValue("DeathWeapon", DeathWeapon);
	section->readStringValue("DrainAnimationType", DrainAnimationType);
	section->readStringValue("ControlledAnimationType", ControlledAnimationType);
	section->readStringValue("PermaControlledAnimationType", PermaControlledAnimationType);
	section->readStringValue("IonCannonWarhead", IonCannonWarhead);

	allocateList(Animation::Array, SplashList);
	WarheadType::Array.findOrAllocate(FlameDamage);
	WarheadType::Array.findOrAllocate(FlameDamage2);
	WarheadType::Array.findOrAllocate(C4Warhead);
	WarheadType::Array.findOrAllocate(CrushWarhead);
	WarheadType::Array.findOrAllocate(V3Warhead);
	WarheadType::Array.findOrAllocate(DMislWarhead);
	WarheadType::Array.findOrAllocate(V3EliteWarhead);
	WarheadType::Array.findOrAllocate(DMislEliteWarhead);
	WarheadType::Array.findOrAllocate(CMislWarhead);
	WarheadType::Array.findOrAllocate(CMislEliteWarhead);
	WarheadType::Array.findOrAllocate(IvanWarhead);

	WeaponType::Array.findOrAllocate(DeathWeapon);
	Animation::Array.findOrAllocate(DrainAnimationType);
	Animation::Array.findOrAllocate(ControlledAnimationType);
	Animation::Array.findOrAllocate(PermaControlledAnimationType);
	WarheadType::Array.findOrAllocate(IonCannonWarhead);
}