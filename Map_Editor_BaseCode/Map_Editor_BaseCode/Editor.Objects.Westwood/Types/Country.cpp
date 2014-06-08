#include "stdafx.h"
#include "Country.hpp"
#include "../../Config.hpp"

/* static */ List<Country> Country::Array;

Country::Country(const std::string& id)
:AbstractType(id)
{

}

void Country::loadRules(INIFile* file)
{
	INISection* rulesSection = file->getSection(ID);
	if (!rulesSection) return;

	AbstractType::loadRules(file);

	rulesSection->readStringValue("Suffix", Suffix);
	rulesSection->readStringValue("Prefix", Prefix);
	rulesSection->readStringValue("Color", Color);
	rulesSection->readBoolValue("Multiplay", Multiplay);
	rulesSection->readBoolValue("MultiplayPassive", MultiplayPassive);
	rulesSection->readStringValue("Side", Side);
	rulesSection->readBoolValue("SmartAI", SmartAI);
	rulesSection->readStringValue("VeteranAircraft", VeteranAircraft);
	rulesSection->readStringValue("VeteranUnits", VeteranUnits);
	rulesSection->readStringValue("VeteranInfantry", VeteranInfantry);
	
	rulesSection->readFloatValue("ArmorAircraftMult", ArmorAircraftMult);
	rulesSection->readFloatValue("ArmorUnitsMult", ArmorUnitsMult);
	rulesSection->readFloatValue("ArmorInfantryMult", ArmorInfantryMult);
	rulesSection->readFloatValue("ArmorBuildingsMult", ArmorBuildingsMult);
	rulesSection->readFloatValue("ArmorDefensesMult", ArmorDefensesMult);
	rulesSection->readFloatValue("CostAircraftMult", CostAircraftMult);
	rulesSection->readFloatValue("CostUnitsMult", CostUnitsMult);
	rulesSection->readFloatValue("CostInfantryMult", CostInfantryMult);
	rulesSection->readFloatValue("CostBuildingsMult", CostBuildingsMult);
	rulesSection->readFloatValue("CostDefensesMult", CostDefensesMult);
	rulesSection->readFloatValue("SpeedAircraftMult", SpeedAircraftMult);
	rulesSection->readFloatValue("SpeedUnitsMult", SpeedUnitsMult);
	rulesSection->readFloatValue("SpeedInfantryMult", SpeedInfantryMult);

	rulesSection->readFloatValue("BuildTimeAircraftMult", BuildTimeAircraftMult);
	rulesSection->readFloatValue("BuildTimeUnitsMult", BuildTimeUnitsMult);
	rulesSection->readFloatValue("BuildTimeInfantryMult", BuildTimeInfantryMult);
	rulesSection->readFloatValue("BuildTimeBuildingsMult", BuildTimeBuildingsMult);
	rulesSection->readFloatValue("BuildTimeDefensesMult", BuildTimeDefensesMult);

	rulesSection->readFloatValue("IncomeMult", IncomeMult);
	rulesSection->readFloatValue("Firepower", Firepower);
	rulesSection->readFloatValue("ROF", ROF);

}

void Country::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	AbstractType::loadArt(art);
}
