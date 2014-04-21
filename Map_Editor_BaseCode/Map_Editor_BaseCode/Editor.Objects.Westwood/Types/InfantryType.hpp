#pragma once

#include <string>
#include "../Managers/List.hpp"
#include "TechnoType.hpp"

class InfantryType : public TechnoType
{
public:
	static List<InfantryType> Array;
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

