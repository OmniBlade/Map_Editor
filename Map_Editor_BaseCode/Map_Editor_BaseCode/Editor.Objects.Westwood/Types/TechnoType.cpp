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

	allocateList(BuildingType::Array, rulesSection->readStringValue("Dock"));
	BuildingType::Array.findOrAllocate(rulesSection->readStringValue("DeploysInto"));
	VehicleType::Array.findOrAllocate(rulesSection->readStringValue("UndeploysInto"));
	VehicleType::Array.findOrAllocate(rulesSection->readStringValue("PowersUnit"));


	allocateList(Animation::Array, rulesSection->readStringValue("Explosion"));
	allocateList(Animation::Array, rulesSection->readStringValue("DestroyAnim"));
	AircraftType::Array.findOrAllocate(rulesSection->readStringValue("AirstrikeTeamType"));
	AircraftType::Array.findOrAllocate(rulesSection->readStringValue("EliteAirstrikeTeamType"));
	VehicleType::Array.findOrAllocate(rulesSection->readStringValue("UnloadingClass"));
	Animation::Array.findOrAllocate(rulesSection->readStringValue("DeployingAnim"));
	InfantryType::Array.findOrAllocate(rulesSection->readStringValue("Enslaves"));
	AircraftType::Array.findOrAllocate(rulesSection->readStringValue("Spawns"));

	Turret = rulesSection->readBoolValue("Turret", Turret);

	IsTrain = rulesSection->readBoolValue("IsTrain", IsTrain);
	Passengers = rulesSection->readIntValue("Passengers", Passengers);
	Size = rulesSection->readFloatValue("Size", Size);
	SizeLimit = rulesSection->readFloatValue("SizeLimit", SizeLimit);

	TechLevel = rulesSection->readIntValue("TechLevel", TechLevel);
	AIBasePlanningSide = rulesSection->readIntValue("AIBasePlanningSide", AIBasePlanningSide);

	NoShadow = rulesSection->readBoolValue("NoShadow", NoShadow);
	ZFudgeCliff = rulesSection->readIntValue("ZFudgeCliff", ZFudgeCliff);
	ZFudgeColumn = rulesSection->readIntValue("ZFudgeColumn", ZFudgeColumn);
	ZFudgeTunnel = rulesSection->readIntValue("ZFudgeTunnel", ZFudgeTunnel);
	ZFudgeBridge = rulesSection->readIntValue("ZFudgeBridge", ZFudgeBridge);
}

void TechnoType::loadArt(INIFile* art)
{
	ObjectType::loadArt(art);
	INISection* artSection = art->getSection(ID);

	Remapable = artSection->readBoolValue("Remapable", false);
	Palette = artSection->readStringValue("Palette", "");

	LineSplitter split(artSection->readStringValue("TurretOffset", "0,0,0"));
	TurretOffset.x = split.pop_int();
	TurretOffset.y = split.pop_int();
	TurretOffset.z = split.pop_int();
}

void TechnoType::loadWeaponTypes(INISection* rulesSection)
{
	DeathWeapon = rulesSection->readStringValue("DeathWeapon", DeathWeapon);
	
	Primary = rulesSection->readStringValue("Primary", Primary);
	Secondary = rulesSection->readStringValue("Secondary", Secondary);
	ElitePrimary = rulesSection->readStringValue("ElitePrimary", ElitePrimary);
	EliteSecondary = rulesSection->readStringValue("EliteSecondary", EliteSecondary);

	WeaponType::Array.findOrAllocate(DeathWeapon);
	WeaponType::Array.findOrAllocate(Primary);
	WeaponType::Array.findOrAllocate(Secondary);
	WeaponType::Array.findOrAllocate(ElitePrimary);
	WeaponType::Array.findOrAllocate(EliteSecondary);
	
	TurretCount = rulesSection->readIntValue("TurretCount", TurretCount);
	WeaponCount = rulesSection->readIntValue("WeaponCount", WeaponCount);

	if (TurretCount <= 0 && WeaponCount <= 0) return; //No gatling means no reading of multiple WeaponTypes!

	//WeaponX.reserve(WeaponCount);
	WeaponX.resize(WeaponCount);
	//EliteWeaponX.reserve(WeaponCount);
	EliteWeaponX.resize(WeaponCount);

	for (int i = 0; i < WeaponCount; ++i)
	{
		std::stringstream number;
		number << i+1;
		std::string weapon = rulesSection->readStringValue("Weapon" + number.str(), WeaponX[i]);
		std::string eWeapon = rulesSection->readStringValue("EliteWeapon" + number.str(), EliteWeaponX[i]);

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