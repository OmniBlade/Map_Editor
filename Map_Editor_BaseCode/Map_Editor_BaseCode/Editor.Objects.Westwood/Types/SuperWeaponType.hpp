#pragma once

#include "../Managers/List.hpp"
#include "AbstractType.hpp"

class SuperWeaponType : public AbstractType
{
public:
	static List<SuperWeaponType> Array;

	SuperWeaponType(const std::string& id);

	void loadRules(INIFile* rules) override;
	void loadArt(INIFile* art) override;

	// rules
	std::string WeaponType = "";
	std::string Payload = ""; //Ares only!
	//Action Action;
	bool IsPowered = true;
	bool DisableableFromShell = true;
	int SidebarFlashTabFrames = -1;
	bool ShowTimer = false;
	//Sound SpecialSound;
	//Sound StartSound;
	float Range = 1.0;
	int LineMultiplier = 1;
	//Type Type;
	//Type PreDependent;
	std::string AuxBuilding = "";
	bool UseChargeDrain = false;
	bool ManualControl = false;
	float RechargeTime = 5.0f;
	std::string SidebarImage = "";
};

