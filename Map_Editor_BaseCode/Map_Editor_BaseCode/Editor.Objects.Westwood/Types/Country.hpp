#pragma once

#include "../Managers/WWList.hpp"
#include "AbstractType.hpp"

class Country : public AbstractType
{
public:
	static WWList<Country> Array;
	Country(const std::string& id);

	void loadRules(INIFile* file) override;
	void loadArt(INIFile* file) override;

	std::string Suffix = "";
	std::string Prefix = "";
	std::string Color = "";
	bool Multiplay = false;
	bool MultiplayPassive = false;
	std::string Side = "";
	bool SmartAI = false;

	std::string VeteranAircraft = "";
	std::string VeteranUnits = "";
	std::string VeteranInfantry = "";

	float ArmorAircraftMult = 1.0f;
	float ArmorUnitsMult = 1.0f;
	float ArmorInfantryMult = 1.0f;
	float ArmorBuildingsMult = 1.0f;
	float ArmorDefensesMult = 1.0f;
	float CostAircraftMult = 1.0f;
	float CostUnitsMult = 1.0f;
	float CostInfantryMult = 1.0f;
	float CostBuildingsMult = 1.0f;
	float CostDefensesMult = 1.0f;
	float SpeedAircraftMult = 1.0f;
	float SpeedUnitsMult = 1.0f;
	float SpeedInfantryMult = 1.0f;

	float BuildTimeAircraftMult = 1.0f;
	float BuildTimeUnitsMult = 1.0f;
	float BuildTimeInfantryMult = 1.0f;
	float BuildTimeBuildingsMult = 1.0f;
	float BuildTimeDefensesMult = 1.0f;

	float IncomeMult = 1.0f;
	float Firepower = 1.0f;
	float ROF = 1.0f;
};

