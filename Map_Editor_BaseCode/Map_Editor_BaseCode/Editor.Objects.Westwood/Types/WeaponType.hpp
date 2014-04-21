#pragma once

#include "../Managers/List.hpp"
#include "AbstractType.hpp"

class WeaponType : public AbstractType
{
public:
	static List<WeaponType> Array;
	WeaponType(const std::string& id);
	
	std::string Projectile = "";

	void loadRules(INIFile* rules) override;
	void loadArt(INIFile* art) override;
};

