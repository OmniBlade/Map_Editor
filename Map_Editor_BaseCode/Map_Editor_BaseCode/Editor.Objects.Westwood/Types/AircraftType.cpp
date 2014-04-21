#include "stdafx.h"
#include "AircraftType.hpp"
#include "../../Log.hpp"

/* static */ List<AircraftType> AircraftType::Array;

AircraftType::AircraftType(const std::string& id)
:TechnoType(id)
{
}

void AircraftType::loadRules(INIFile* rules)
{
	INISection* rulesSection = rules->getSection(ID);
	if (!rulesSection) return;

	TechnoType::loadRules(rules);
	
	Fighter = rulesSection->readBoolValue("Fighter", Fighter);
	CarryAll = rulesSection->readBoolValue("CarryAll", CarryAll);
}

void AircraftType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	TechnoType::loadArt(art);
}
