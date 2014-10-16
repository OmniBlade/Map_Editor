#include "stdafx.h"
#include "Country.hpp"
#include "../../Config.hpp"
#include "../../Editor.FileSystem/MapFile/WriterHelper.h"

/* static */ WWList<Country> Country::Array;

Country::Country(const std::string& id)
:AbstractType(id)
{

}

void Country::loadRules(INIFile* file)
{
	INISection* rulesSection = file->getSection(ID);
	if (!rulesSection) return;

	AbstractType::loadRules(file);

	rulesSection->readStringValue("ParentCountry", ParentCountry);
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

void Country::writeToINI(INIFile& file)
{
	std::stringstream number;
	int i = 0;
	for (auto& it : Array.typeList)
	{
		if (!it->isGlobal)
		{
			number << i;
			file.SetValue("Countries", number.str(), it->ID);
			++i;
			number.str(std::string());
			it->writeContentToINI(file);
		}
	}
}

void Country::writeContentToINI(INIFile& file)
{
	if (!ParentCountry.empty())
		file.SetValue(ID.c_str(), "ParentCountry", ParentCountry);
	file.SetValue(ID.c_str(), "Name", Name);
	file.SetValue(ID.c_str(), "Suffix", Suffix);
	file.SetValue(ID.c_str(), "Prefix", Prefix);
	file.SetValue(ID.c_str(), "Color", Color);
	file.SetValue(ID.c_str(), "Side", Side);
	if (Multiplay) file.SetValue(ID.c_str(), "Multiplay", BoolWriter::getBoolString(Multiplay, BoolWriter::BoolType::TRUEFALSE));
	if (MultiplayPassive) file.SetValue(ID.c_str(), "MultiplayPassive", BoolWriter::getBoolString(MultiplayPassive, BoolWriter::BoolType::TRUEFALSE));
	file.SetValue(ID.c_str(), "SmartAI", BoolWriter::getBoolString(SmartAI, BoolWriter::BoolType::YESNO));
	file.SetValue(ID.c_str(), "Side", Side);
}

