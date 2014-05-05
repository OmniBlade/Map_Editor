#include "stdafx.h"
#include "SuperWeaponType.hpp"
#include "BuildingType.hpp"
#include "../../Log.hpp"
#include "WeaponType.hpp"
#include "../../Config.hpp"

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

	rulesSection->readStringValue("WeaponType", WeaponType);
	WeaponType::Array.findOrAllocate(WeaponType);

	rulesSection->readStringValue("AuxBuilding", AuxBuilding);
	BuildingType::Array.findOrAllocate(AuxBuilding);

	if (Config::hasAres)
	{
		rulesSection->readStringValue("Nuke.Payload", Payload);
		WeaponType::Array.findOrAllocate(Payload);
	}

	rulesSection->readBoolValue("IsPowered", IsPowered);
	rulesSection->readBoolValue("DisableFromShell", DisableableFromShell);
	rulesSection->readIntValue("SidebarFlashTabFrames", SidebarFlashTabFrames);
	rulesSection->readBoolValue("ShowTimer", ShowTimer);
	rulesSection->readFloatValue("Range", Range);
	rulesSection->readIntValue("LineMultiplier", LineMultiplier);
	rulesSection->readBoolValue("UseChargeDrain", UseChargeDrain);
	rulesSection->readBoolValue("ManualControl", ManualControl);
	rulesSection->readFloatValue("RechargeTime", RechargeTime);
	rulesSection->readStringValue("SidebarImage", SidebarImage);

}

void SuperWeaponType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	AbstractType::loadArt(art);
}
