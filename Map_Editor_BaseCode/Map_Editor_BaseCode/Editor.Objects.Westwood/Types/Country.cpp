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
			}
		}
	}

	for (const auto& it : Array.typeList)
	{
		if (!it->isGlobal)
		{
			it->writeContentToINI(file);
		}
		/*
			Countries cannot exist as a local House
			WW used it in their missions (Houses with the same name as the country)

			Will fix when people use Houses that inherit from their Country with the same ID
			The game accepts it!
		*/
		else if (it->isGlobal && it->hasMapMod && !House::Array.exists(it->ID))
		{
			it->writeContentToINI(file);
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

