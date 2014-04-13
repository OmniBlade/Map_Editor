#pragma once

#include "TechnoType.hpp"

#include <string>


class AircraftType : public TechnoType
{
public:
	AircraftType(INISection* _rulesSection, INISection* _artSection);

	void loadRules() override;
	void loadArt() override;

	bool Fighter;
	bool CarryAll;

protected:
	INISection* rulesSection = nullptr;
	INISection* artSection = nullptr;
};

