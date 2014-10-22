#include "stdafx.h"
#include "MapMods.h"
#include "../../Editor.Engine/Types/Managers/MapObjectList.hpp"
#include "../../Editor.Objects.Westwood/Types/OverlayType.hpp"
#include "../../Editor.Objects.Westwood/Types/SuperWeaponType.hpp"
#include "../../Editor.Objects.Westwood/Types/WarheadType.hpp"
#include "../../Editor.Objects.Westwood/Types/SmudgeType.hpp"
#include "../../Editor.Objects.Westwood/Types/TerrainType.hpp"
#include "../../Editor.Objects.Westwood/Types/BuildingType.hpp"
#include "../../Editor.Objects.Westwood/Types/VehicleType.hpp"
#include "../../Editor.Objects.Westwood/Types/InfantryType.hpp"
#include "../../Editor.Objects.Westwood/Types/AircraftType.hpp"
#include "../../Editor.Objects.Westwood/Types/Animation.hpp"
#include "../../Editor.Objects.Westwood/Types/VoxelAnimType.hpp"
#include "../../Editor.Objects.Westwood/Types/ParticleType.hpp"
#include "../../Editor.Objects.Westwood/Types/WeaponType.hpp"
#include "MapModsHelper.h"
#include "../INIFile/INIFile.hpp"
#include "../FileManager/Managers/INIManager.hpp"
#include "../../Editor.Engine/Types/House.hpp"
#include "../../Editor.Objects.Westwood/Types/Country.hpp"
#include "../../Editor.Engine/Types/AI/AITriggerType.hpp"
#include "../../Editor.Engine/Types/TeamTypes/ScriptType.hpp"
#include "../../Editor.Engine/Types/TeamTypes/TeamType.hpp"
#include "../../Editor.Engine/Types/TeamTypes/TaskForce.hpp"
#include "../FileManager/Managers/INIManager.hpp"
#include "../../Editor.Engine/Game/GameModeCollection.hpp"
#include "../../Config.hpp"


/* static */ MapMods* MapMods::pInstance;
/* static */ MapMods* MapMods::instance()
{
	if (!pInstance)
	{
		pInstance = new MapMods();
	}
	else
	{
		return pInstance;
	}
	return pInstance;
}

MapMods::MapMods()
{
}

MapMods::~MapMods()
{
}

void MapMods::writeToINI(INIFile& file)
{
	auto pIt = instance();
	pIt->filterNonDifferentMods();
	pIt->writeFoaSections(file);
	pIt->writeGenericSections(file);

	//Leftovers will be written
	for (auto& it : pIt->modsFile->getSectionList())
	{
		file.addSectionByCopy(pIt->modsFile->getSection(it), true);
	}
}

void MapMods::parse(INIFile* map)
{
	modsFile = map; //lol
}

std::string MapMods::getComparisonValue(const std::string& section, const std::string& key)
{
	const auto pRules = INIManager::instance()->get(Config::rules);
	const auto pMode = GameModeCollection::getInstance()->getCurrent() ? INIManager::instance()->get(GameModeCollection::getInstance()->getCurrent()->iniName) : nullptr;

	std::string modeValue = pMode ? pMode->getSection(section.c_str())->getValue(key.c_str()) : "";

	INISection* pSection = pRules->getSection(section.c_str());
	const std::string& rValue = pSection ? pSection->getValue(key.c_str()) : "";

	return modeValue.empty() ? rValue : modeValue;
}

void MapMods::filterNonDifferentMods()
{
	for (const auto& aSection : modsFile->getSectionList())
	{
		auto pSection = modsFile->getSection(aSection);
		for (auto& key : pSection->getKeys())
		{
			if (pSection->getValue(key.c_str()) == getComparisonValue(aSection, key))
			{
				pSection->deleteKeyValue(key.c_str());
			}
		}

		if (!pSection->size())
		{
			modsFile->deleteSection(aSection.c_str());
		}
	}
}

void MapMods::writeGenericSections(INIFile& file)
{
	auto pGeneral = modsFile->getSection("General");
	if (pGeneral)
	{
		file.addSectionByCopy(pGeneral, true);
		modsFile->deleteSection("General");
	}

	auto pAVisual = modsFile->getSection("AudioVisual");
	if (pAVisual)
	{
		file.addSectionByCopy(pAVisual, true);
		modsFile->deleteSection("AudioVisual");
	}
}

void MapMods::writeFoaSections(INIFile& file)
{		
	writeAFoaSection(Country::Array, "Countries", file);
	writeAFoaSection(WeaponType::Array, "", file);
	writeAFoaSection(ParticleType::Array, "Particles", file);
	writeAFoaSection(VoxelAnimType::Array, "VoxelAnims", file);
	writeAFoaSection(Animation::Array, "Animations", file);
	writeAFoaSection(InfantryType::Array, "InfantryTypes", file);
	writeAFoaSection(AircraftType::Array, "AircraftTypes", file);
	writeAFoaSection(VehicleType::Array, "VehicleTypes", file);
	writeAFoaSection(BuildingType::Array, "BuildingTypes", file);
	writeAFoaSection(TerrainType::Array, "TerrainTypes", file);
	writeAFoaSection(SmudgeType::Array, "SmudgeTypes", file);
	writeAFoaSection(WarheadType::Array, "Warheads", file);
	writeAFoaSection(SuperWeaponType::Array, "SuperWeaponTypes", file);
	writeAFoaSection(OverlayType::Array, "OverlayTypes", file);
}
