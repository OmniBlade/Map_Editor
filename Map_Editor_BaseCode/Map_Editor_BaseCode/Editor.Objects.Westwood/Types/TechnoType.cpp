#include "stdafx.h"
#include "TechnoType.hpp"
#include "../../Editor.FileSystem/INIFile/LineSplitter.hpp"
#include "../../Log.hpp"
#include "../General/EntryHelper.hpp"
#include "WeaponType.hpp"
#include "Animation.hpp"
#include "VoxelAnimType.hpp"
#include "BuildingType.hpp"
#include "VehicleType.hpp"
#include "AircraftType.hpp"
#include "InfantryType.hpp"
#include <sstream>

TechnoType::TechnoType(const std::string& id)
:ObjectType(id)
{
}

void TechnoType::loadRules(INIFile* rules)
{
	ObjectType::loadRules(rules);
	INISection* rulesSection = rules->getSection(ID);

	loadWeaponTypes(rulesSection);

	rulesSection->readStringValue("Dock", Dock);
	rulesSection->readStringValue("DeploysInto", DeploysInto);
	rulesSection->readStringValue("UndeploysInto", UndeploysInto);
	rulesSection->readStringValue("PowersUnit", PowersUnit);
	rulesSection->readStringValue("Explosion", Explosion);
	rulesSection->readStringValue("DestroyAnim", DestroyAnim);
	rulesSection->readStringValue("AirstrikeTeamType", AirstrikeTeamType);
	rulesSection->readStringValue("EliteAirstrikeTeamType", EliteAirstrikeTeamType);
	rulesSection->readStringValue("UnloadingClass", UnloadingClass);
	rulesSection->readStringValue("DeployingAnim", DeployingAnim);
	rulesSection->readStringValue("Enslaves", Enslaves);
	rulesSection->readStringValue("Spawns", Spawns);

	allocateList(BuildingType::Array, Dock);
	BuildingType::Array.findOrAllocate(DeploysInto);
	VehicleType::Array.findOrAllocate(UndeploysInto);
	VehicleType::Array.findOrAllocate(PowersUnit);


	allocateList(Animation::Array, Explosion);
	allocateList(Animation::Array, DestroyAnim);
	AircraftType::Array.findOrAllocate(AirstrikeTeamType);
	AircraftType::Array.findOrAllocate(EliteAirstrikeTeamType);
	VehicleType::Array.findOrAllocate(UnloadingClass);
	Animation::Array.findOrAllocate(DeployingAnim);
	InfantryType::Array.findOrAllocate(Enslaves);
	AircraftType::Array.findOrAllocate(Spawns);

	 rulesSection->readBoolValue("Turret", Turret);

	rulesSection->readBoolValue("IsTrain", IsTrain);
	rulesSection->readIntValue("Passengers", Passengers);
	rulesSection->readFloatValue("Size", Size);
	rulesSection->readFloatValue("SizeLimit", SizeLimit);

	rulesSection->readIntValue("TechLevel", TechLevel);
	rulesSection->readIntValue("AIBasePlanningSide", AIBasePlanningSide);

	rulesSection->readBoolValue("NoShadow", NoShadow);
	rulesSection->readIntValue("ZFudgeCliff", ZFudgeCliff);
	rulesSection->readIntValue("ZFudgeColumn", ZFudgeColumn);
	rulesSection->readIntValue("ZFudgeTunnel", ZFudgeTunnel);
	rulesSection->readIntValue("ZFudgeBridge", ZFudgeBridge);
}

void TechnoType::loadArt(INIFile* art)
{
	ObjectType::loadArt(art);
	INISection* artSection = art->getSection(ID);

	artSection->readBoolValue("Remapable", Remapable);
	artSection->readStringValue("Palette", Palette);

	artSection->readStringValue("TurretOffset", TurretOffsetStr);
	LineSplitter split(TurretOffsetStr);
	TurretOffset.x = split.pop_int();
	TurretOffset.y = split.pop_int();
	TurretOffset.z = split.pop_int();
}

void TechnoType::loadWeaponTypes(INISection* rulesSection)
{
	rulesSection->readStringValue("DeathWeapon", DeathWeapon);
	rulesSection->readBoolValue("Gattling.Cycle", GattlingCycle);
	rulesSection->readStringValue("Primary", Primary);
	rulesSection->readStringValue("Secondary", Secondary);
	rulesSection->readStringValue("ElitePrimary", ElitePrimary);
	rulesSection->readStringValue("EliteSecondary", EliteSecondary);

	WeaponType::Array.findOrAllocate(DeathWeapon);
	if (!GattlingCycle)
	{
		WeaponType::Array.findOrAllocate(Primary);
		WeaponType::Array.findOrAllocate(Secondary);
		WeaponType::Array.findOrAllocate(ElitePrimary);
		WeaponType::Array.findOrAllocate(EliteSecondary);
	}
	
	rulesSection->readIntValue("TurretCount", TurretCount);
	rulesSection->readIntValue("WeaponCount", WeaponCount);

	if (TurretCount <= 0 && WeaponCount <= 0) return; //No gatling means no reading of multiple WeaponTypes!

	//WeaponX.reserve(WeaponCount);
	WeaponX.resize(WeaponCount);
	//EliteWeaponX.reserve(WeaponCount);
	EliteWeaponX.resize(WeaponCount);

	for (int i = 0; i < WeaponCount; ++i)
	{
		std::stringstream number;
		number << i+1;
		std::string weapon, eWeapon;
		rulesSection->readStringValue("Weapon" + number.str(), weapon, WeaponX[i]);
		rulesSection->readStringValue("EliteWeapon" + number.str(), eWeapon, EliteWeaponX[i]);

		if (weapon != "")
			WeaponX[i] = weapon;
		if (eWeapon != "")
			EliteWeaponX[i] = eWeapon;

		number.str(std::string());
	}

	/* For safety measures (Elite)WeaponX are being processed separately to prevent out of range crashes */

	for (int i = 0; i < WeaponCount; ++i)
	{
		//Create WeaponType
		WeaponType::Array.findOrAllocate(WeaponX[i]);
		WeaponType::Array.findOrAllocate(EliteWeaponX[i]);
	}
}