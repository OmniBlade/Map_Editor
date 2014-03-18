#pragma once

#include "TechnoType.hpp"

class VehicleType : public TechnoType
{
public:
	VehicleType(INISection* _rulesSection, INISection* _artSection);

	void loadRules() override;
	void loadArt() override;

	bool Harvester;
	bool Weeder;
	bool UseTurretShadow;

	//Art
	int StandingFrames;
	int Facings;


protected:
	INISection* rulesSection = nullptr;
	INISection* artSection = nullptr;
};

