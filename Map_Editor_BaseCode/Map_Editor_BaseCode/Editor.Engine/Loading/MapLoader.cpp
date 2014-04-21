#include "stdafx.h"
#include "MapLoader.hpp"
#include "../../Log.hpp"
#include "../../Config.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "MapLoaderHelpers.hpp"
#include "../../Editor.Objects.Westwood/Managers/ListHelpers.hpp"
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

MapLoader::MapLoader()
{
	general = new General("General");
	ai = new AI();
	specialWeapons = new SpecialWeapon();
	audioVisual = new AudioVisual();
	combatDamage = new CombatDamage();
}

void MapLoader::allocateMainRules(INIFile* file, INIFile* art)
{
	Log::note("Allocating main rules now...", Log::DEBUG);

	//general->loadRules(file);
	allocateAll(Country::Array, file, "Countries");
	allocateAll(OverlayType::Array, file, "OverlayTypes");
	allocateAll(SuperWeaponType::Array, file, "SuperWeaponTypes");
	allocateAll(WarheadType::Array, file, "Warheads");
	allocateAll(SmudgeType::Array, file, "SmudgeTypes");
	allocateAll(TerrainType::Array, file, "TerrainTypes");
	allocateAll(BuildingType::Array, file, "BuildingTypes");
	//insertNukePayload();
	allocateAll(VehicleType::Array, file, "VehicleTypes");
	allocateAll(AircraftType::Array, file, "AircraftTypes");
	allocateAll(InfantryType::Array, file, "InfantryTypes");
	allocateAll(Animation::Array, file, "Animations");
	insertDAnimation();
	allocateAll(VoxelAnimType::Array, file, "VoxelAnims");
	allocateAll(ParticleType::Array, file, "Particles");
	//allocateAll(WeaponType::Array, file, "WeaponTypes");

	ai->loadRules(file);
	general->loadRules(file);
}

void MapLoader::loadAll(INIFile* file, INIFile* art)
{
	Log::note("Loading main rules now...", Log::DEBUG);
	//3 times for rules / gamemode mode / mapmod
	loadFromINI(Country::Array, *file, *art);
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
	loadFromINI(BuildingType::Array, *file, *art);
	loadFromINI(TerrainType::Array, *file, *art);
	loadFromINI(SmudgeType::Array, *file, *art);
	loadFromINI(OverlayType::Array, *file, *art);
	loadFromINI(ParticleType::Array, *file, *art);
	loadFromINI(VoxelAnimType::Array, *file, *art);

	combatDamage->loadRules(file);
	audioVisual->loadRules(file);
	specialWeapons->loadRules(file);
	//loadFromINI(ProjectileType::Array, *file, *art);

	
	//Log::note("===================Dumping Animations!", Log::DEBUG);
	//Country::Array.dumpContent();
	//Log::note("===================Dumping Animations!", Log::DEBUG);
	//ParticleType::Array.dumpContent();
	/*Log::note("Dumping WeaponTypes!", Log::DEBUG);
	WeaponType::Array.dumpContent();
	Log::note("Dumping Projectiles!", Log::DEBUG);
	ProjectileType::Array.dumpContent();
	Log::note("Dumping InfantryTypes!", Log::DEBUG);
	InfantryType::Array.dumpContent();
	Log::note("Dumping VehicleTypes!", Log::DEBUG);
	VehicleType::Array.dumpContent();
	Log::note("Dumping AircraftTypes!", Log::DEBUG);
	AircraftType::Array.dumpContent();
	Log::note("Dumping BuildingTypes!", Log::DEBUG);
	BuildingType::Array.dumpContent();
	Log::note("Dumping SuperWeaponTypes!", Log::DEBUG);
	SuperWeaponType::Array.dumpContent();
	Log::note("Dumping SmudgeTypes!", Log::DEBUG);
	SmudgeType::Array.dumpContent();
	Log::note("Dumping Particles!", Log::DEBUG);
	ParticleType::Array.dumpContent();
	*/
}

void MapLoader::loadArtAll(INIFile* art)
{
	// This shit happens once!

}

void MapLoader::insertNukePayload()
{
	for (unsigned int i = 0; i < WeaponType::Array.typeList.size(); ++i)
	{
		if (WeaponType::Array.typeList.at(i).get()->ID == "NukePayload")
		{
			WeaponType::Array.typeList.erase(WeaponType::Array.typeList.begin() + i);
			break;
		}
	}
	WeaponType::Array.typeList.insert(WeaponType::Array.typeList.begin() + 2, std::make_unique<WeaponType>("NukePayload"));
}

void MapLoader::insertDAnimation()
{
	Animation::Array.findOrAllocate("D");
}

/*
[Countries]
[SuperWeaponTypes]
[AnimTypes]
[BuildingTypes]
[AircraftTypes]
[UnitTypes]
[InfantryTypes]
[WeaponTypes]
[ProjectileTypes]
[WarheadTypes]
[BuildingTypes]
[TerrainTypes]
[SmudgeTypes]
[OverlayTypes]
[Particles]
[ParticleSystems]
[VoxelAnimTypes]
MissionControl
*/
