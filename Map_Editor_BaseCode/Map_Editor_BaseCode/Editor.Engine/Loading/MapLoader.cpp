#include "stdafx.h"
#include "MapLoader.hpp"
#include "../../Log.hpp"
#include "../../Config.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "MapLoaderHelpers.hpp"
#include "../../Editor.Objects.Westwood/Managers/WWListHelpers.hpp"
#include "../Types/Managers/MapObjectListHelpers.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Editor.Objects.Westwood/Types/OverlayType.hpp"
#include "../../Editor.Objects.Westwood/Types/SuperWeaponType.hpp"
#include "../../Editor.Objects.Westwood/Types/SmudgeType.hpp"
#include "../../Editor.Objects.Westwood/Types/TerrainType.hpp"
#include "../../Editor.Objects.Westwood/Types/BuildingType.hpp"
#include "../../Editor.Objects.Westwood/Types/VehicleType.hpp"
#include "../../Editor.Objects.Westwood/Types/AircraftType.hpp"
#include "../../Editor.Objects.Westwood/Types/InfantryType.hpp"
#include "../../Editor.Objects.Westwood/Types/VoxelAnimType.hpp"
#include "../../Editor.Objects.Westwood/Types/ParticleType.hpp"
#include "../../Editor.Objects.Westwood/Types/Animation.hpp"
#include "../../Editor.Objects.Westwood/Types/WeaponType.hpp"
#include "../../Editor.Objects.Westwood/Types/ProjectileType.hpp"
#include "../../Editor.Objects.Westwood/Types/WarheadType.hpp"
#include "../../Editor.Objects.Westwood/Types/Country.hpp"
#include "../../Editor.Objects.Westwood/Types/Tiberium.hpp"
#include "../../Editor.Objects.Westwood/AudioVisual/Sound.hpp"
#include "../../Editor.Objects.Westwood/AudioVisual/Speech.hpp"
#include "../../Editor.Objects.Westwood/AudioVisual/Theme.hpp"
#include "../../Editor.Objects.Westwood/AudioVisual/Movie.h"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Editor.Engine/Game/GameModeCollection.hpp"
#include "../Types/VariableName.hpp"
#include "../Types/TeamTypes/ScriptType.hpp"
#include "../Types/TeamTypes/TaskForce.hpp"
#include "../Types/TeamTypes/TeamType.hpp"
#include "../Types/AI/AITriggerType.hpp"

MapLoader::MapLoader()
{
	general = new General("General");
	ai = new AI();
	specialWeapons = new SpecialWeapon();
	audioVisual = new AudioVisual();
	combatDamage = new CombatDamage();
	sides = new Side();
	iq = new IQ();

	//Initiate Sound, Speech and Theme here, they have no real dependency anyhow
	loadAudio();
}

void MapLoader::load(INIFile* file, const std::string& name)
{
	if (!file)
	{
		Log::line("Unable to allocate rules, '" + name + "' file doesn't exist!", Log::DEBUG);
		return;
	}

	allocateMainRules(file, name);
	loadAll(file, name);
}

void MapLoader::allocateMainRules(INIFile* file, const std::string& name)
{
	Log::line("Allocating main rules now for '" + name + "'...", Log::DEBUG);

	allocateAll(Country::Array, file, "Countries");
	allocateAll(OverlayType::Array, file, "OverlayTypes");
	allocateAll(SuperWeaponType::Array, file, "SuperWeaponTypes");
	allocateAll(WarheadType::Array, file, "Warheads");
	allocateAll(SmudgeType::Array, file, "SmudgeTypes");
	allocateAll(TerrainType::Array, file, "TerrainTypes");
	allocateAll(BuildingType::Array, file, "BuildingTypes");
	allocateAll(VehicleType::Array, file, "VehicleTypes");
	allocateAll(AircraftType::Array, file, "AircraftTypes");
	allocateAll(InfantryType::Array, file, "InfantryTypes");
	allocateAll(Animation::Array, file, "Animations");
	insertDAnimation();
	allocateAll(VoxelAnimType::Array, file, "VoxelAnims");
	allocateAll(ParticleType::Array, file, "Particles");
	allocateAll(Tiberium::Array, file, "Tiberiums");

	ai->loadRules(file);
	iq->loadRules(file);
	general->loadRules(file);

	if (Config::hasAres)
		allocateAll(WeaponType::Array, file, "WeaponTypes");

}

void MapLoader::loadAll(INIFile* file, const std::string& name)
{
	INIFile* art = INIManager::instance()->get(Config::art);

	Log::line("Loading main rules now for '" + name + "'...", Log::DEBUG);
	//3 times for rules / gamemode mode / mapmod
	loadFromINI(Country::Array, *file, *art);
	sides->loadRules(file);
	loadFromINI(SuperWeaponType::Array, *file, *art);
	loadFromINI(Animation::Array, *file, *art);
	loadFromINI(BuildingType::Array, *file, *art);
	insertNukePayload();
	loadFromINI(AircraftType::Array, *file, *art);
	loadFromINI(VehicleType::Array, *file, *art);
	loadFromINI(InfantryType::Array, *file, *art);
	loadFromINI(WeaponType::Array, *file, *art);
	loadFromINI(ProjectileType::Array, *file, *art);
	loadFromINI(WarheadType::Array, *file, *art);
	//loadFromINI(BuildingType::Array, *file, *art);
	loadFromINI(TerrainType::Array, *file, *art);
	loadFromINI(SmudgeType::Array, *file, *art);
	loadFromINI(OverlayType::Array, *file, *art);
	loadFromINI(ParticleType::Array, *file, *art);
	loadFromINI(VoxelAnimType::Array, *file, *art);

	combatDamage->loadRules(file);
	audioVisual->loadRules(file);
	specialWeapons->loadRules(file);
	loadFromINI(Tiberium::Array, *file, *art);
	loadFromINI(WeaponType::Array, *file, *art); //Again
}

void MapLoader::loadAudio()
{
	INIFile* speech = INIManager::instance()->get(Config::eva);
	INIFile* sound = INIManager::instance()->get(Config::sound);
	INIFile* theme = INIManager::instance()->get(Config::theme);
	INIFile* art = INIManager::instance()->get(Config::art);
	
	allocateAll(Speech::Array, speech, "DialogList");
	allocateAll(Sound::Array, sound, "SoundList");
	allocateAll(Theme::Array, theme, "Themes");
	loadFromSingleINI(Speech::Array, *speech);
	loadFromSingleINI(Sound::Array, *sound);
	loadFromSingleINI(Theme::Array, *theme);

	INISection* movielist = art->getSection("Movies");
	INISection& uglySection = *movielist;

	for (const auto& it : uglySection)
	{
		Movie::Array.make();
		Movie::Array.typeList[Movie::Array.count() - 1].get()->parse(it, uglySection.getValue(it.c_str()));
	}
}

void MapLoader::loadAI()
{
	INIFile* aimd = INIManager::instance()->get(Config::AI);

	allocateAll(TeamType::Array, aimd, "TeamTypes");
	allocateAll(TaskForce::Array, aimd, "TaskForces");
	allocateAll(ScriptType::Array, aimd, "ScriptTypes");
	loadAllocatedINI(TeamType::Array, *aimd, true);
	loadAllocatedINI(TaskForce::Array, *aimd, true);
	loadAllocatedINI(ScriptType::Array, *aimd, true);
	loadAIFromINI(AITriggerType::Array, *aimd, "AITriggerTypes", true);

}

void MapLoader::loadGlobalVariable()
{
	INIFile* rules = INIManager::instance()->get(Config::rules);
	INISection* globals = rules->getSection("VariableNames");

	INISection& uglySection = *globals;

	for (const auto& it : uglySection)
	{
		GlobalVariableName::Array.make();
		GlobalVariableName::Array.objectList[GlobalVariableName::Array.count() - 1].get()->parse(it, uglySection.getValue(it.c_str()));
	}
}

bool MapLoader::locateGameMode(INIFile* map)
{
	INISection* basic = map->getSection("Basic");
	
	if (!basic->keyExists("GameMode") || basic->keyExists("Player"))
	{
		return false;
	}

	LineSplitter split(basic->getValue("GameMode"));
	if (split.size() > 1 && (split.size() == 2 && !split.exists("standard")))
	{
		Log::line("Multiple game modes are found, none are loaded to maintain proper lists!", Log::DEBUG);
		return false;
	}
	else if (split.empty())
	{
		Log::line("GameMode key exists in map file, but no game modes are defined!", Log::DEBUG);
		return false;
	}
	else if (split.size() == 1 || (split.size() == 2 && split.exists("standard")))
	{
		if (split.peek_string() == "standard" && split.size() == 2)
		{
			split.pop_string();
			GameModeCollection::getInstance()->setCurrent(split.pop_string());
		}
		else
			GameModeCollection::getInstance()->setCurrent(split.pop_string());
		return true;
	}
	return false;
}

void MapLoader::dumpLists()
{
	if (!Config::dumpTypes) return;

	Log::line();
	Log::line(" === PARSED DATA DUMP === ", Log::DEBUG);
	Log::line("Dumping types, 'X' means the object is invalid and will be hidden from", Log::DEBUG);
	Log::line("the actual lists in the editor. 'V' means the object is valid and visible", Log::EXTRA);
	Log::line("in the lists. Content should be very close to the game's representation.", Log::EXTRA);

	Log::line();
	Log::line("[Animations]", Log::DEBUG);
	Animation::Array.dumpContent();
	Log::line();
	Log::line("[WeaponTypes]", Log::DEBUG);
	WeaponType::Array.dumpContent();
	Log::line();
	Log::line("[Warheads]", Log::DEBUG);
	WarheadType::Array.dumpContent();
	Log::line();
	Log::line("[Projectiles]", Log::DEBUG);
	ProjectileType::Array.dumpContent();
	Log::line();
	Log::line("[Countries]", Log::DEBUG);
	Country::Array.dumpContent();
	Log::line();
	Log::line("[InfantryTypes]", Log::DEBUG);
	InfantryType::Array.dumpContent();
	Log::line();
	Log::line("[VehicleTypes]", Log::DEBUG);
	VehicleType::Array.dumpContent();
	Log::line();
	Log::line("[AircraftTypes]", Log::DEBUG);
	AircraftType::Array.dumpContent();
	Log::line();
	Log::line("[BuildingTypes]", Log::DEBUG);
	BuildingType::Array.dumpContent();
	Log::line();
	Log::line("[SuperWeaponTypes]", Log::DEBUG);
	SuperWeaponType::Array.dumpContent();
	Log::line();
	Log::line("[SmudgeTypes]", Log::DEBUG);
	SmudgeType::Array.dumpContent();
	Log::line();
	Log::line("[OverlayTypes]", Log::DEBUG);
	OverlayType::Array.dumpContent();
	Log::line();
	Log::line("[Particles]", Log::DEBUG);
	ParticleType::Array.dumpContent();
}

/*
	If Ares is used, no explicit hardcoding is needed
	If NukePayload does not exist after parsing, it will be inserted at index 2 after all
*/
void MapLoader::insertNukePayload()
{
	for (unsigned int i = 0; i < WeaponType::Array.typeList.size(); ++i)
	{
		if (Config::hasAres) break;

		/*
			Because every time it is re-inserted into the list, it isn't valid at the last run
			This check, to see if NukePayload is already at index 2, should fix the issue
		*/
		if (i == 2 && WeaponType::Array.typeList[i]->ID == "NukePayload")
			return;

		if (WeaponType::Array.typeList.at(i).get()->ID == "NukePayload" && i != 2)
		{
			WeaponType::Array.typeList.erase(WeaponType::Array.typeList.begin() + i);
			WeaponType::Array.typeList.insert(WeaponType::Array.typeList.begin() + 2, std::make_unique<WeaponType>("NukePayload"));
			return;
		}
	}

	if (WeaponType::Array.find("NukePayload") == nullptr && WeaponType::Array.count() >= 3)
		WeaponType::Array.typeList.insert(WeaponType::Array.typeList.begin() + 2, std::make_unique<WeaponType>("NukePayload"));
}

void MapLoader::insertDAnimation()
{
	Animation::Array.findOrAllocate("D");
}

void MapLoader::setGlobalCountries()
{
	for (auto& it : Country::Array.typeList)
	{
		it->setGlobal(true);
	}
}

/*void MapLoader::loadMPCountries()
{
	Country::Array.findOrAllocate("<Player @ A>");
	Country::Array.findOrAllocate("<Player @ B>");
	Country::Array.findOrAllocate("<Player @ C>");
	Country::Array.findOrAllocate("<Player @ D>");
	Country::Array.findOrAllocate("<Player @ E>");
	Country::Array.findOrAllocate("<Player @ F>");
	Country::Array.findOrAllocate("<Player @ G>");
	Country::Array.findOrAllocate("<Player @ H>");
}*/
