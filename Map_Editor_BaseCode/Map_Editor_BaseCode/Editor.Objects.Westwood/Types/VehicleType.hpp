#pragma once

#include "TechnoType.hpp"
#include "../Managers/List.hpp"

class VehicleType : public TechnoType
{
public:
	static List<VehicleType> Array;
	VehicleType(const std::string& id);

	void loadRules(INIFile* rules) override;
	void loadArt(INIFile* rules) override;

	bool Harvester = false;
	bool Weeder = false;
	bool UseTurretShadow = false;

	//Art
	int StandingFrames;
	int Facings;
};
