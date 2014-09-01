#pragma once

#include "TechnoType.hpp"
#include "../Managers/WWList.hpp"
#include <string>


class AircraftType : public TechnoType
{
public:
	static WWList<AircraftType> Array;
	AircraftType(const std::string& id);

	void loadRules(INIFile* rules) override;
	void loadArt(INIFile* art) override;

	bool Fighter = false;
	bool CarryAll = false;

protected:
};

