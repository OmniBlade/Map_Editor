#pragma once

#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include <string>

class CombatDamage
{
public:
	CombatDamage();
	void loadRules(INIFile* file);

	std::string SplashList;
	std::string FlameDamage;
	std::string FlameDamage2;
	std::string C4Warhead;
	std::string CrushWarhead;
	std::string V3Warhead;
	std::string DMislWarhead;
	std::string V3EliteWarhead;
	std::string DMislEliteWarhead;
	std::string CMislWarhead;
	std::string CMislEliteWarhead;
	std::string IvanWarhead;

	std::string DeathWeapon;
	std::string DrainAnimationType;
	std::string ControlledAnimationType;
	std::string PermaControlledAnimationType;
	std::string IonCannonWarhead;
};

