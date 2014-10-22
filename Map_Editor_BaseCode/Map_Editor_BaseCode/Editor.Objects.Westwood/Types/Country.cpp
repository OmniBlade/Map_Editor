#include "stdafx.h"
#include "Country.hpp"
#include "../../Config.hpp"
#include "../../Editor.FileSystem/MapFile/WriterHelper.h"
#include "../General/Side.hpp"
#include "../../Editor.Engine/Types/Managers/MapObjectList.hpp"
#include "../../Editor.Engine/Types/House.hpp"

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
	sideIndex = Side::instance()->getSideIndexByName(Side);
	rulesSection->readBoolValue("SmartAI", SmartAI);

	/*
	rulesSection->readDeletableStringValue("VeteranAircraft", VeteranAircraft);
	rulesSection->readDeletableStringValue("VeteranUnits", VeteranUnits);
	rulesSection->readDeletableStringValue("VeteranInfantry", VeteranInfantry);
	
	rulesSection->readDeletableFloatValue("ArmorAircraftMult", ArmorAircraftMult);
	rulesSection->readDeletableFloatValue("ArmorUnitsMult", ArmorUnitsMult);
	rulesSection->readDeletableFloatValue("ArmorInfantryMult", ArmorInfantryMult);
	rulesSection->readDeletableFloatValue("ArmorBuildingsMult", ArmorBuildingsMult);
	rulesSection->readDeletableFloatValue("ArmorDefensesMult", ArmorDefensesMult);
	rulesSection->readDeletableFloatValue("CostAircraftMult", CostAircraftMult);
	rulesSection->readDeletableFloatValue("CostUnitsMult", CostUnitsMult);
	rulesSection->readDeletableFloatValue("CostInfantryMult", CostInfantryMult);
	rulesSection->readDeletableFloatValue("CostBuildingsMult", CostBuildingsMult);
	rulesSection->readDeletableFloatValue("CostDefensesMult", CostDefensesMult);
	rulesSection->readDeletableFloatValue("SpeedAircraftMult", SpeedAircraftMult);
	rulesSection->readDeletableFloatValue("SpeedUnitsMult", SpeedUnitsMult);
	rulesSection->readDeletableFloatValue("SpeedInfantryMult", SpeedInfantryMult);

	rulesSection->readDeletableFloatValue("BuildTimeAircraftMult", BuildTimeAircraftMult);
	rulesSection->readDeletableFloatValue("BuildTimeUnitsMult", BuildTimeUnitsMult);
	rulesSection->readDeletableFloatValue("BuildTimeInfantryMult", BuildTimeInfantryMult);
	rulesSection->readDeletableFloatValue("BuildTimeBuildingsMult", BuildTimeBuildingsMult);
	rulesSection->readDeletableFloatValue("BuildTimeDefensesMult", BuildTimeDefensesMult);

	rulesSection->readDeletableFloatValue("IncomeMult", IncomeMult);
	rulesSection->readDeletableFloatValue("Firepower", Firepower);
	rulesSection->readDeletableFloatValue("ROF", ROF);
	*/
	//if (!rulesSection->size())
	//{
	//	file->deleteSection(ID.c_str());
	//}
}

void Country::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	AbstractType::loadArt(art);
}

void Country::writeToINI(INIFile& file)
{
	if (containsLocalCountries())
	{
		std::stringstream number;
		int i = 0;

		for (const auto& it : Array.typeList)
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
}

bool Country::containsLocalCountries()
{
	for (auto& it : Array.typeList)
	{
		if (!it->isGlobal)
			return true;
	}
	return false;
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

	return;

	//Yawn...
	//Apparently it's needed otherwise Country objects are recognized as map mods when writing, and thus end up in wrong places
	if(!VeteranAircraft.empty()) file.SetValue(ID.c_str(), "VeteranAircraft", VeteranAircraft);
	if(!VeteranUnits.empty()) file.SetValue(ID.c_str(), "VeteranUnits", VeteranUnits);
	if(!VeteranInfantry.empty()) file.SetValue(ID.c_str(), "VeteranInfantry", VeteranInfantry);

	if (ArmorAircraftMult != 1.0f) file.SetValue(ID.c_str(), "ArmorAircraftMult", Log::toString(ArmorAircraftMult));
	if (ArmorUnitsMult != 1.0f) file.SetValue(ID.c_str(), "ArmorUnitsMult", Log::toString(ArmorUnitsMult));
	if (ArmorInfantryMult != 1.0f) file.SetValue(ID.c_str(), "ArmorInfantryMult", Log::toString(ArmorInfantryMult));
	if (ArmorBuildingsMult != 1.0f) file.SetValue(ID.c_str(), "ArmorBuildingsMult", Log::toString(ArmorBuildingsMult));
	if (ArmorDefensesMult != 1.0f) file.SetValue(ID.c_str(), "ArmorDefensesMult", Log::toString(ArmorDefensesMult));
	if (CostAircraftMult != 1.0f) file.SetValue(ID.c_str(), "CostAircraftMult", Log::toString(CostAircraftMult));
	if (CostUnitsMult != 1.0f) file.SetValue(ID.c_str(), "CostUnitsMult", Log::toString(CostUnitsMult));
	if (CostInfantryMult != 1.0f) file.SetValue(ID.c_str(), "CostInfantryMult", Log::toString(CostInfantryMult));
	if (CostBuildingsMult != 1.0f) file.SetValue(ID.c_str(), "CostBuildingsMult", Log::toString(CostBuildingsMult));
	if (CostDefensesMult != 1.0f) file.SetValue(ID.c_str(), "CostDefensesMult", Log::toString(CostDefensesMult));
	if (SpeedAircraftMult != 1.0f) file.SetValue(ID.c_str(), "SpeedAircraftMult", Log::toString(SpeedAircraftMult));
	if (SpeedUnitsMult != 1.0f) file.SetValue(ID.c_str(), "SpeedUnitsMult", Log::toString(SpeedUnitsMult));
	if (SpeedInfantryMult != 1.0f) file.SetValue(ID.c_str(), "SpeedInfantryMult", Log::toString(SpeedInfantryMult));
	if (BuildTimeAircraftMult != 1.0f) file.SetValue(ID.c_str(), "BuildTimeAircraftMult", Log::toString(BuildTimeAircraftMult));
	if (BuildTimeUnitsMult != 1.0f) file.SetValue(ID.c_str(), "BuildTimeUnitsMult", Log::toString(BuildTimeUnitsMult));
	if (BuildTimeInfantryMult != 1.0f) file.SetValue(ID.c_str(), "BuildTimeInfantryMult", Log::toString(BuildTimeInfantryMult));
	if (BuildTimeBuildingsMult != 1.0f) file.SetValue(ID.c_str(), "BuildTimeBuildingsMult", Log::toString(BuildTimeBuildingsMult));
	if (BuildTimeDefensesMult != 1.0f) file.SetValue(ID.c_str(), "BuildTimeDefensesMult", Log::toString(BuildTimeDefensesMult));

	if (IncomeMult != 1.0f) file.SetValue(ID.c_str(), "IncomeMult", Log::toString(IncomeMult));
	if (Firepower != 1.0f) file.SetValue(ID.c_str(), "Firepower", Log::toString(Firepower));
	if (ROF != 1.0f) file.SetValue(ID.c_str(), "ROF", Log::toString(ROF));
}

