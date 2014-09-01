#pragma once

#include "AbstractType.hpp"
#include "../Managers/WWList.hpp"

class ProjectileType : public AbstractType
{
public:
	static WWList<ProjectileType> Array;
	ProjectileType(const std::string& id);

	void loadRules(INIFile* rules) override;
	void loadArt(INIFile* art) override;

	std::string AirburstWeapon;
	std::string ShrapnelWeapon;
	std::string Image;
	std::string Trailer;
};

