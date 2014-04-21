#include "stdafx.h"
#include "SuperWeaponType.hpp"
#include "BuildingType.hpp"
#include "../../Log.hpp"
#include "WeaponType.hpp"

/* static */ List<SuperWeaponType> SuperWeaponType::Array;

SuperWeaponType::SuperWeaponType(const std::string& id)
:AbstractType(id)
{

}

void SuperWeaponType::loadRules(INIFile* rules)
{
	INISection* rulesSection = rules->getSection(ID);
	if (!rulesSection) return;

	AbstractType::loadRules(rules);

	WeaponType = rulesSection->readStringValue("WeaponType", WeaponType);
	if (WeaponType != "")
		WeaponType::Array.findOrAllocate(WeaponType);

	AuxBuilding = rulesSection->readStringValue("AuxBuilding", AuxBuilding);
	if (AuxBuilding != "")
		BuildingType::Array.findOrAllocate(AuxBuilding);

	IsPowered = rulesSection->readBoolValue("IsPowered", IsPowered);
	DisableableFromShell = rulesSection->readBoolValue("DisableFromShell", DisableableFromShell);
	SidebarFlashTabFrames = rulesSection->readIntValue("SidebarFlashTabFrames", SidebarFlashTabFrames);
	ShowTimer = rulesSection->readBoolValue("ShowTimer", ShowTimer);
	Range = rulesSection->readFloatValue("Range", Range);
	LineMultiplier = rulesSection->readIntValue("LineMultiplier", LineMultiplier);
	UseChargeDrain = rulesSection->readBoolValue("UseChargeDrain", UseChargeDrain);
	ManualControl = rulesSection->readBoolValue("ManualControl", ManualControl);
	RechargeTime = rulesSection->readFloatValue("RechargeTime", RechargeTime);
	SidebarImage = rulesSection->readStringValue("SidebarImage", SidebarImage);
}

void SuperWeaponType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	AbstractType::loadArt(art);
}
