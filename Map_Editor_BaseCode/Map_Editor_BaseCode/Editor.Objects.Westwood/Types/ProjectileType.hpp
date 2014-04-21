#pragma once

#include "AbstractType.hpp"
#include "../Managers/List.hpp"

class ProjectileType : public AbstractType
{
public:
	static List<ProjectileType> Array;
	ProjectileType(const std::string& id);

	std::string AirburstWeapon = "";
	std::string ShrapnelWeapon = "";
	std::string Image = "";

	void loadRules(INIFile* rules) override;
	void loadArt(INIFile* art) override;
	void loadWeaponTypes(INISection* section);

};

