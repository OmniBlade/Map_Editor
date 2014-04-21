#include "stdafx.h"
#include "VehicleType.hpp"
#include "../../Log.hpp"

/* static */ List<VehicleType> VehicleType::Array;

VehicleType::VehicleType(const std::string& id)
:TechnoType(id)
{
}

void VehicleType::loadRules(INIFile* rules)
{
	INISection* rulesSection = rules->getSection(ID);
	if (!rulesSection) return;

	TechnoType::loadRules(rules);
	
	Harvester = rulesSection->readBoolValue("Harvester", Harvester);
	Weeder = rulesSection->readBoolValue("Weeder", Weeder);
	UseTurretShadow = rulesSection->readBoolValue("UseTurretShadow", UseTurretShadow);
}

void VehicleType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;
	
	TechnoType::loadArt(art);
	
	StandingFrames = artSection->readIntValue("StandingFrames", 0);
	Facings = artSection->readIntValue("Facings", 8);

}
