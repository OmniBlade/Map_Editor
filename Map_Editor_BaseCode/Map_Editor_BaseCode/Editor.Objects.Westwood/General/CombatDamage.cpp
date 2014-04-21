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

	allocateList(Animation::Array, section->readStringValue("SplashList"));
	WarheadType::Array.findOrAllocate(section->readStringValue("FlameDamage"));
	WarheadType::Array.findOrAllocate(section->readStringValue("FlameDamage2"));
	WarheadType::Array.findOrAllocate(section->readStringValue("C4Warhead"));
	WarheadType::Array.findOrAllocate(section->readStringValue("CrushWarhead"));
	WarheadType::Array.findOrAllocate(section->readStringValue("V3Warhead"));
	WarheadType::Array.findOrAllocate(section->readStringValue("DMislWarhead"));
	WarheadType::Array.findOrAllocate(section->readStringValue("V3EliteWarhead"));
	WarheadType::Array.findOrAllocate(section->readStringValue("DMislEliteWarhead"));
	WarheadType::Array.findOrAllocate(section->readStringValue("CMislWarhead"));
	WarheadType::Array.findOrAllocate(section->readStringValue("CMislEliteWarhead"));
	WarheadType::Array.findOrAllocate(section->readStringValue("IvanWarhead"));

	WeaponType::Array.findOrAllocate(section->readStringValue("DeathWeapon"));
	Animation::Array.findOrAllocate(section->readStringValue("DrainAnimationType"));
	Animation::Array.findOrAllocate(section->readStringValue("ControlledAnimationType"));
	Animation::Array.findOrAllocate(section->readStringValue("PermaControlledAnimationType"));
	WarheadType::Array.findOrAllocate(section->readStringValue("IonCannonWarhead"));
}