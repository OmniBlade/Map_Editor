#pragma once

#include <string>
#include "../Managers/WWList.hpp"
#include "TechnoType.hpp"

class InfantryType : public TechnoType
{
public:
	static WWList<InfantryType> Array;
	InfantryType(const std::string& id);

	void loadRules(INIFile* rules) override;
	void loadArt(INIFile* art) override;

	std::string OccupyWeapon = "";
	std::string EliteOccupyWeapon = "";

	bool Cyborg = false;
	bool NotHuman = false;
	bool Occupier = false;
	bool Civilian = false;
};

