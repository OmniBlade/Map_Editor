#pragma once

#include <string>
#include "ObjectType.hpp"
#include "../Vector3D.hpp"

class TechnoType : public ObjectType
{
public:
	TechnoType(const std::string& id);
	
	void loadRules(INIFile* rules) override;
	void loadArt(INIFile* art) override;
	void loadWeaponTypes(INISection* section);

	std::string Dock;
	std::string DeploysInto;
	std::string UndeploysInto;
	std::string PowersUnit;
	std::string Explosion;
	std::string DestroyAnim;
	std::string AirstrikeTeamType;
	std::string EliteAirstrikeTeamType;
	std::string UnloadingClass;
	std::string DeployingAnim;
	std::string Enslaves;
	std::string Spawns;

	bool IsTrain = false;
	int Passengers = 0;
	float Size = 1.0f;
	float SizeLimit = 0.0f;
	int WeaponCount = 0;
	int TurretCount = 0;
	//Weapons need to be added here! Gotta love Action #42

	std::string DeathWeapon;
	std::string Primary;
	std::string Secondary;
	std::string ElitePrimary;
	std::string EliteSecondary;
	std::vector<std::string> WeaponX;
	std::vector<std::string> EliteWeaponX;

	bool Turret = false;
	bool GattlingCycle = false;
	int TechLevel = 255;
	int AIBasePlanningSide = -1;
	bool NoShadow = false;
	int ZFudgeCliff = 10;
	int ZFudgeColumn = 5;
	int ZFudgeTunnel = 10;
	int ZFudgeBridge = 0;
	
	// Art
	std::string Palette;
	std::string TurretOffsetStr = "0,0,0";
	Vector3D TurretOffset; //TODO: Rework this in 3DVector class
	bool Remapable;	//This would work for TS though...
	//TODO: Weapon stuff gotta be added here too, right? "WeaponXBarrelLength" etc


	/*
		All the properties that are used by all types
		Please note: I decided to list all the flags like they are in the INI
	*
	//RULES FLAGS
	int TechLevel; // Used to tell the user what unit can and cannot be build (threshold 1 - 10?)
	int AIBasePlanningSide; // Most def needed with Ares
	int Passengers;				// Isn't this only used by Aircraft and Vehicles?
	float Weight;				// Something about passengers
	float PhysicalSize;			// This too
	float Size;					// This too, related to tag below
	float SizeLimit;			// Largest type of unit allowed?

	
	//bool ConsideredAircraft; // This could be useful for something, until it is leave it commented out
	
	bool IsTrain; // This should be used for 'Follows ID' on trains and wagons*/
};

