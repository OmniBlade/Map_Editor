#include "stdafx.h"
#include "AircraftType.hpp"
#include "../../Log.hpp"

/* static */ WWList<AircraftType> AircraftType::Array;

AircraftType::AircraftType(const std::string& id)
:TechnoType(id)
{
}

void AircraftType::loadRules(INIFile* rules)
{
	INISection* rulesSection = rules->getSection(ID);
	if (!rulesSection) return;

	TechnoType::loadRules(rules);
	
	rulesSection->readBoolValue("Fighter", Fighter, Fighter);
	rulesSection->readBoolValue("CarryAll", CarryAll, CarryAll);
}

void AircraftType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	TechnoType::loadArt(art);
}
