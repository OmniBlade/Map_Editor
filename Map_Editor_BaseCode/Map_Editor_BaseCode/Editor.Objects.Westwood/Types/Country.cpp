#include "stdafx.h"
#include "Country.hpp"

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

	Suffix = rulesSection->readStringValue("Suffix", Suffix);
	Prefix = rulesSection->readStringValue("Prefix", Prefix);
	Color = rulesSection->readStringValue("Color", Color);
	Multiplay = rulesSection->readBoolValue("Multiplay", Multiplay);
	MultiplayPassive = rulesSection->readBoolValue("MultiplayPassive", MultiplayPassive);
	Side = rulesSection->readStringValue("Side", Side);
	SmartAI = rulesSection->readBoolValue("SmartAI", SmartAI);
	VeteranAircraft = rulesSection->readStringValue("VeteranAircraft", VeteranAircraft);
	VeteranUnits = rulesSection->readStringValue("VeteranUnits", VeteranUnits);
	VeteranInfantry = rulesSection->readStringValue("VeteranInfantry", VeteranInfantry);
	
	ArmorAircraftMult = rulesSection->readFloatValue("ArmorAircraftMult", ArmorAircraftMult);
	ArmorUnitsMult = rulesSection->readFloatValue("ArmorUnitsMult", ArmorUnitsMult);
	ArmorInfantryMult = rulesSection->readFloatValue("ArmorInfantryMult", ArmorInfantryMult);
	ArmorBuildingsMult = rulesSection->readFloatValue("ArmorBuildingsMult", ArmorBuildingsMult);
	ArmorDefensesMult = rulesSection->readFloatValue("ArmorDefensesMult", ArmorDefensesMult);
	CostAircraftMult = rulesSection->readFloatValue("CostAircraftMult", CostAircraftMult);
	CostUnitsMult = rulesSection->readFloatValue("CostUnitsMult", CostUnitsMult);
	CostInfantryMult = rulesSection->readFloatValue("CostInfantryMult", CostInfantryMult);
	CostBuildingsMult = rulesSection->readFloatValue("CostBuildingsMult", CostBuildingsMult);
	CostDefensesMult = rulesSection->readFloatValue("CostDefensesMult", CostDefensesMult);
	SpeedAircraftMult = rulesSection->readFloatValue("SpeedAircraftMult", SpeedAircraftMult);
	SpeedUnitsMult = rulesSection->readFloatValue("SpeedUnitsMult", SpeedUnitsMult);
	SpeedInfantryMult = rulesSection->readFloatValue("SpeedInfantryMult", SpeedInfantryMult);

	BuildTimeAircraftMult = rulesSection->readFloatValue("BuildTimeAircraftMult", BuildTimeAircraftMult);
	BuildTimeUnitsMult = rulesSection->readFloatValue("BuildTimeUnitsMult", BuildTimeUnitsMult);
	BuildTimeInfantryMult = rulesSection->readFloatValue("BuildTimeInfantryMult", BuildTimeInfantryMult);
	BuildTimeBuildingsMult = rulesSection->readFloatValue("BuildTimeBuildingsMult", BuildTimeBuildingsMult);
	BuildTimeDefensesMult = rulesSection->readFloatValue("BuildTimeDefensesMult", BuildTimeDefensesMult);

	IncomeMult = rulesSection->readFloatValue("IncomeMult", IncomeMult);
	Firepower = rulesSection->readFloatValue("Firepower", Firepower);
	ROF = rulesSection->readFloatValue("ROF", ROF);

}

void Country::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	AbstractType::loadArt(art);
}