#pragma once

#include "../Managers/WWList.hpp"
#include "AbstractType.hpp"

class WeaponType : public AbstractType
{
public:
	static WWList<WeaponType> Array;
	WeaponType(const std::string& id);
	
	void loadRules(INIFile* rules) override;
	void loadArt(INIFile* art) override;

	std::string Projectile, Warhead, Anim;
};

