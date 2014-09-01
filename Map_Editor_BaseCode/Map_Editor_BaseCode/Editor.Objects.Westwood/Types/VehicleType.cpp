#include "stdafx.h"
#include "VehicleType.hpp"
#include "../../Log.hpp"

/* static */ WWList<VehicleType> VehicleType::Array;

VehicleType::VehicleType(const std::string& id)
:TechnoType(id)
{
}

void VehicleType::loadRules(INIFile* rules)
{
	INISection* rulesSection = rules->getSection(ID);
	if (!rulesSection) return;

	TechnoType::loadRules(rules);
	
	rulesSection->readBoolValue("Harvester", Harvester);
	rulesSection->readBoolValue("Weeder", Weeder);
	rulesSection->readBoolValue("UseTurretShadow", UseTurretShadow);
}

void VehicleType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;
	
	TechnoType::loadArt(art);
	
	artSection->readIntValue("StandingFrames", StandingFrames);
	artSection->readIntValue("Facings", Facings);

}
