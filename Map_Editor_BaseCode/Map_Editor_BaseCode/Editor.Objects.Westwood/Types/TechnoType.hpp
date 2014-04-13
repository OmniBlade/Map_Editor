#pragma once

#include <string>
#include "ObjectType.hpp"
#include "../Vector3D.hpp"

class TechnoType : public ObjectType
{
public:
	TechnoType(INISection* _rulesSection, INISection* _artSection);
	
	void loadRules() override;
	void loadArt() override;

	bool IsTrain;
	int Passengers;
	float Size;
	float SizeLimit;
	//Weapons need to be added here! Gotta love Action #42
	bool Turret;
	int TechLevel;
	int AIBasePlanningSide;
	bool NoShadow;
	int ZFudgeCliff;
	int ZFudgeColumn;
	int ZFudgeTunnel;
	int ZFudgeBridge;
	std::string Palette;
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

protected:
	INISection* rulesSection = nullptr;
	INISection* artSection = nullptr;
};

