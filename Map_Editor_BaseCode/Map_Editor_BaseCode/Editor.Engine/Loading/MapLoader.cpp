#include "stdafx.h"
#include "MapLoader.hpp"
#include "../../Log.hpp"
#include "../../Config.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "MapLoaderHelpers.hpp"
#include "../../Editor.Objects.Westwood/Managers/ListHelpers.hpp"
#include "../Types/Managers/ObjectListHelpers.hpp"
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
#include "../../Editor.Objects.Westwood/Audio/Sound.hpp"
#include "../../Editor.Objects.Westwood/Audio/Speech.hpp"
#include "../../Editor.Objects.Westwood/Audio/Theme.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Editor.Engine/Game/GameModeCollection.hpp"
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

void MapLoader::load(INIFile* file)
{
	if (!file)
	{
		Log::note("Unable to allocate rules, file doesn't exist!", Log::DEBUG);
		return;
	}

	allocateMainRules(file);
	loadAll(file);
}

void MapLoader::allocateMainRules(INIFile* file)
{
	Log::note("Allocating main rules now...", Log::DEBUG);

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

void MapLoader::loadAll(INIFile* file)
{
	INIFile* art = INIManager::getManager()->get(Config::art);

	Log::note("Loading main rules now...", Log::DEBUG);
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
	INIFile* speech = INIManager::getManager()->get(Config::eva);
	INIFile* sound = INIManager::getManager()->get(Config::sound);
	INIFile* theme = INIManager::getManager()->get(Config::theme);
	
	allocateAll(Speech::Array, speech, "DialogList");
	allocateAll(Sound::Array, sound, "SoundList");//
	allocateAll(Theme::Array, theme, "Themes");//
	loadFromSingleINI(Speech::Array, *speech);
	loadFromSingleINI(Sound::Array, *sound);
	loadFromSingleINI(Theme::Array, *theme);
}

void MapLoader::loadAI()
{
	INIFile* aimd = INIManager::getManager()->get(Config::AI);

	allocateAll(TeamType::Array, aimd, "TeamTypes");
	allocateAll(TaskForce::Array, aimd, "TaskForces");
	allocateAll(ScriptType::Array, aimd, "ScriptTypes");
	loadAllocatedINI(TeamType::Array, *aimd, true);
	loadAllocatedINI(TaskForce::Array, *aimd, true);
	loadAllocatedINI(ScriptType::Array, *aimd, true);
	loadFromINI(AITriggerType::Array, *aimd, "AITriggerTypes");
}

bool MapLoader::locateGameMode(INIFile* map)
{
	INISection* basic = map->getSection("Basic");
	
	if (!basic->checkKeyExistance("GameMode") || basic->checkKeyExistance("Player"))
	{
		return false;
	}

	LineSplitter split(basic->getValue("GameMode"));

	if (split.size() > 1)
	{
		Log::note("Multiple game modes are found, none are loaded to maintain proper lists!", Log::DEBUG);
		return false;
	}
	else if (split.empty())
	{
		Log::note("GameMode key exists in map file, but no game modes are defined!", Log::DEBUG);
		return false;
	}
	else if (split.size() == 1)
	{
		GameModeCollection::getInstance()->setCurrent(split.pop_string());
		return true;
	}
}

void MapLoader::dumpLists()
{
	if (!Config::dumpTypes) return;

	Log::note("Dumping parsed types to output file, refer to that file for types reference", Log::DEBUG);
	Log::line("Dumping types, 'X' means the object is invalid and will be hidden from", Log::INFO);
	Log::line("the actual lists in the editor. 'V' means the object is valid and visible", Log::EXTRAS);
	Log::line("in the lists. Content should be very close to the game's representation.", Log::EXTRAS);

	Log::line();
	Log::line("[Animations]", Log::INFO);
	Animation::Array.dumpContent();
	Log::line();
	Log::line("[WeaponTypes]", Log::INFO);
	WeaponType::Array.dumpContent();
	Log::line();
	Log::line("[Warheads]", Log::INFO);
	WarheadType::Array.dumpContent();
	Log::line();
	Log::line("[Projectiles]", Log::INFO);
	ProjectileType::Array.dumpContent();
	Log::line();
	Log::line("[Countries]", Log::INFO);
	Country::Array.dumpContent();
	Log::line();
	Log::line("[InfantryTypes]", Log::INFO);
	InfantryType::Array.dumpContent();
	Log::line();
	Log::line("[VehicleTypes]", Log::INFO);
	VehicleType::Array.dumpContent();
	Log::line();
	Log::line("[AircraftTypes]", Log::INFO);
	AircraftType::Array.dumpContent();
	Log::line();
	Log::line("[BuildingTypes]", Log::INFO);
	BuildingType::Array.dumpContent();
	Log::line();
	Log::line("[SuperWeaponTypes]", Log::INFO);
	SuperWeaponType::Array.dumpContent();
	Log::line();
	Log::line("[SmudgeTypes]", Log::INFO);
	SmudgeType::Array.dumpContent();
	Log::line();
	Log::line("[OverlayTypes]", Log::INFO);
	OverlayType::Array.dumpContent();
	Log::line();
	Log::line("[Particles]", Log::INFO);
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

		if (WeaponType::Array.typeList.at(i).get()->ID == "NukePayload")
		{
			WeaponType::Array.typeList.erase(WeaponType::Array.typeList.begin() + i);
			WeaponType::Array.typeList.insert(WeaponType::Array.typeList.begin() + 2, std::make_unique<WeaponType>("NukePayload"));
			return;
		}
	}

	if (WeaponType::Array.find("NukePayload") == nullptr)
		WeaponType::Array.typeList.insert(WeaponType::Array.typeList.begin() + 2, std::make_unique<WeaponType>("NukePayload"));
}

void MapLoader::insertDAnimation()
{
	Animation::Array.findOrAllocate("D");
}