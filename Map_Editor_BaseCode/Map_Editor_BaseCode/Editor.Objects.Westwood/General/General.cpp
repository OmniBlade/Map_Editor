#include "stdafx.h"
#include "General.hpp"
#include "../Types/Animation.hpp"
#include "../Types/VehicleType.hpp"
#include "../Types/InfantryType.hpp"
#include "../Types/TerrainType.hpp"
#include "../Types/BuildingType.hpp"
#include "../Types/WeaponType.hpp"
#include "../Types/AircraftType.hpp"
#include "../Types/VoxelAnimType.hpp"
#include "../Types/WarheadType.hpp"
#include "EntryHelper.hpp"

General::General(const std::string& id)
:AbstractType(id)
{

}

void General::loadRules(INIFile* file)
{
	INISection* section = file->getSection(ID);
	if (!section) return;

	AbstractType::loadRules(file);

	section->readStringValue("DamageFireTypes", DamageFireTypes);
	section->readStringValue("OreTwinkle", OreTwinkle);
	section->readStringValue("BarrelExplode", BarrelExplode);
	section->readStringValue("NukeTakeOff", NukeTakeOff);
	section->readStringValue("Wake", Wake);
	section->readStringValue("DropPod", DropPod);
	section->readStringValue("DeadBodies", DeadBodies);
	section->readStringValue("MetallicDebris", MetallicDebris);
	section->readStringValue("BridgeExplosions", BridgeExplosions);
	section->readStringValue("IonBlast", IonBlast);
	section->readStringValue("WeatherConClouds", WeatherConClouds);

	section->readStringValue("WeatherConBoltExplosion", WeatherConBoltExplosion);
	section->readStringValue("DominatorWarhead", DominatorWarhead);
	section->readStringValue("DominatorFirstAnim", DominatorFirstAnim);
	section->readStringValue("DominatorSecondAnim", DominatorSecondAnim);
	section->readStringValue("ChronoPlacement", ChronoPlacement);
	section->readStringValue("ChronoBeam", ChronoBeam);
	section->readStringValue("ChronoBlast", ChronoBlast);
	section->readStringValue("ChronoBlastDest", ChronoBlastDest);
	section->readStringValue("WarpIn", WarpIn);
	section->readStringValue("WarpOut", WarpOut);
	section->readStringValue("WarpAway", WarpAway);
	section->readStringValue("IronCurtainInvokeAnim", IronCurtainInvokeAnim);
	section->readStringValue("ForceShieldInvokeAnim", ForceShieldInvokeAnim);
	section->readStringValue("WeaponNullifyAnim", WeaponNullifyAnim);
	section->readStringValue("ChronoSparkle1", ChronoSparkle1);
	section->readStringValue("InfantryExplode", InfantryExplode);
	section->readStringValue("FlamingInfantry", FlamingInfantry);
	section->readStringValue("InfantryHeadPop", InfantryHeadPop);
	section->readStringValue("InfantryNuked", InfantryNuked);
	section->readStringValue("InfantryVirus", InfantryVirus);
	section->readStringValue("InfantryBrute", InfantryBrute);
	section->readStringValue("InfantryMutate", InfantryMutate);
	section->readStringValue("Behind", Behind);
	section->readStringValue("MoveFlash", MoveFlash);
	section->readStringValue("Parachute", Parachute);
	section->readStringValue("BombParachute", BombParachute);
	section->readStringValue("DropZoneAnim", DropZoneAnim);
	section->readStringValue("EMPulseSparkles", EMPulseSparkles);
	section->readStringValue("LargeVisceroid", LargeVisceroid);
	section->readStringValue("SmallVisceroid", SmallVisceroid);
	section->readStringValue("DropPodWeapon", DropPodWeapon);
	section->readStringValue("ExplosiveVoxelDebris", ExplosiveVoxelDebris);
	section->readStringValue("TireVoxelDebris", TireVoxelDebris);
	section->readStringValue("ScrapVoxelDebris", ScrapVoxelDebris);
	section->readStringValue("RepairBay", RepairBay);
	section->readStringValue("GDIGateOne", GDIGateOne);
	section->readStringValue("GDIGateTwo", GDIGateTwo);
	section->readStringValue("NodGateOne", NodGateOne);
	section->readStringValue("NodGateTwo", NodGateTwo);
	section->readStringValue("WallTower", WallTower);
	section->readStringValue("Shipyard", Shipyard);
	section->readStringValue("GDIPowerPlant", GDIPowerPlant);
	section->readStringValue("NodRegularPower", NodRegularPower);
	section->readStringValue("NodAdvancedPower", NodAdvancedPower);
	section->readStringValue("ThirdPowerPlant", ThirdPowerPlant);
	section->readStringValue("PrerequisiteProcAlternate", PrerequisiteProcAlternate);
	section->readStringValue("BaseUnit", BaseUnit);
	section->readStringValue("HarvesterUnit", HarvesterUnit);
	section->readStringValue("PadAircraft", PadAircraft);
	section->readStringValue("Paratrooper", Paratrooper);
	section->readStringValue("SecretInfantry", SecretInfantry);
	section->readStringValue("SecretUnits", SecretUnits);
	section->readStringValue("SecretBuildings", SecretBuildings);
	section->readStringValue("AlliedDisguise", AlliedDisguise);
	section->readStringValue("SovietDisguise", SovietDisguise);
	section->readStringValue("ThirdDisguise", ThirdDisguise);
	section->readStringValue("Engineer", Engineer);
	section->readStringValue("Technician", Technician);
	section->readStringValue("Pilot", Pilot);
	section->readStringValue("AlliedCrew", AlliedCrew);
	section->readStringValue("SovietCrew", SovietCrew);
	section->readStringValue("ThirdCrew", ThirdCrew);
	section->readStringValue("AmerParaDropInf", AmerParaDropInf);
	section->readStringValue("AllyParaDropInf", AllyParaDropInf);
	section->readStringValue("SovParaDropInf", SovParaDropInf);
	section->readStringValue("YuriParaDropInf", YuriParaDropInf);
	section->readStringValue("AnimToInfantry", AnimToInfantry);
	section->readStringValue("LightningWarhead", LightningWarhead);
	section->readStringValue("PrismType", PrismType);
	section->readStringValue("V3RocketType", V3RocketType);
	section->readStringValue("DMislType", DMislType);
	section->readStringValue("CMislType", CMislType);
	section->readStringValue("VeinholeTypeClass", VeinholeTypeClass);
	section->readStringValue("DefaultMirageDisguises", DefaultMirageDisguises);


	allocateList(Animation::Array, DamageFireTypes);
	allocateList(Animation::Array, OreTwinkle);
	allocateList(Animation::Array, BarrelExplode);
	allocateList(Animation::Array, NukeTakeOff);
	allocateList(Animation::Array, Wake);
	allocateList(Animation::Array, DropPod);
	allocateList(Animation::Array, DeadBodies);
	allocateList(Animation::Array, MetallicDebris);
	allocateList(Animation::Array, BridgeExplosions);
	allocateList(Animation::Array, IonBlast);
	allocateList(Animation::Array, WeatherConClouds);
	//allocateList(Animation::Array, section->readStringValue("WeatherConBolts", WeatherConBolts));3
	Animation::Array.findOrAllocate(WeatherConBoltExplosion);
	WarheadType::Array.findOrAllocate(DominatorWarhead);
	Animation::Array.findOrAllocate(DominatorFirstAnim);
	Animation::Array.findOrAllocate(DominatorSecondAnim);
	Animation::Array.findOrAllocate(ChronoPlacement);
	Animation::Array.findOrAllocate(ChronoBeam);
	Animation::Array.findOrAllocate(ChronoBlast);
	Animation::Array.findOrAllocate(ChronoBlastDest);
	Animation::Array.findOrAllocate(WarpIn);
	Animation::Array.findOrAllocate(WarpOut);
	Animation::Array.findOrAllocate(WarpAway);
	Animation::Array.findOrAllocate(IronCurtainInvokeAnim);
	Animation::Array.findOrAllocate(ForceShieldInvokeAnim);
	Animation::Array.findOrAllocate(WeaponNullifyAnim);
	Animation::Array.findOrAllocate(ChronoSparkle1);
	Animation::Array.findOrAllocate(InfantryExplode);
	Animation::Array.findOrAllocate(FlamingInfantry);
	Animation::Array.findOrAllocate(InfantryHeadPop);
	Animation::Array.findOrAllocate(InfantryNuked);
	Animation::Array.findOrAllocate(InfantryVirus);
	Animation::Array.findOrAllocate(InfantryBrute);
	Animation::Array.findOrAllocate(InfantryMutate);
	Animation::Array.findOrAllocate(Behind);
	Animation::Array.findOrAllocate(MoveFlash);
	Animation::Array.findOrAllocate(Parachute);
	Animation::Array.findOrAllocate(BombParachute);
	Animation::Array.findOrAllocate(DropZoneAnim);
	Animation::Array.findOrAllocate(EMPulseSparkles);

	VehicleType::Array.findOrAllocate(LargeVisceroid);
	VehicleType::Array.findOrAllocate(SmallVisceroid);
	WeaponType::Array.findOrAllocate(DropPodWeapon);


	allocateList(VoxelAnimType::Array, ExplosiveVoxelDebris);
	VoxelAnimType::Array.findOrAllocate(TireVoxelDebris);
	VoxelAnimType::Array.findOrAllocate(ScrapVoxelDebris);

	allocateList(BuildingType::Array, RepairBay);
	BuildingType::Array.findOrAllocate(GDIGateOne);
	BuildingType::Array.findOrAllocate(GDIGateTwo);
	BuildingType::Array.findOrAllocate(NodGateOne);
	BuildingType::Array.findOrAllocate(NodGateTwo);
	BuildingType::Array.findOrAllocate(WallTower);
	allocateList(BuildingType::Array, Shipyard);	
	BuildingType::Array.findOrAllocate(GDIPowerPlant);
	BuildingType::Array.findOrAllocate(NodRegularPower);
	BuildingType::Array.findOrAllocate(NodAdvancedPower);
	BuildingType::Array.findOrAllocate(ThirdPowerPlant);
	VehicleType::Array.findOrAllocate(PrerequisiteProcAlternate);
	allocateList(VehicleType::Array, BaseUnit);
	allocateList(VehicleType::Array, HarvesterUnit);
	allocateList(AircraftType::Array, PadAircraft);
	InfantryType::Array.findOrAllocate(Paratrooper);
	allocateList(InfantryType::Array, SecretInfantry);
	allocateList(VehicleType::Array, SecretUnits);
	allocateList(BuildingType::Array, SecretBuildings);
	InfantryType::Array.findOrAllocate(AlliedDisguise);
	InfantryType::Array.findOrAllocate(SovietDisguise);
	InfantryType::Array.findOrAllocate(ThirdDisguise);
	InfantryType::Array.findOrAllocate(Engineer);
	InfantryType::Array.findOrAllocate(Technician);
	InfantryType::Array.findOrAllocate(Pilot);
	InfantryType::Array.findOrAllocate(AlliedCrew);
	InfantryType::Array.findOrAllocate(SovietCrew);
	InfantryType::Array.findOrAllocate(ThirdCrew);
	allocateList(InfantryType::Array, AmerParaDropInf);
	allocateList(InfantryType::Array, AllyParaDropInf);
	allocateList(InfantryType::Array, SovParaDropInf);
	allocateList(InfantryType::Array, YuriParaDropInf);
	allocateList(InfantryType::Array, AnimToInfantry);
	WarheadType::Array.findOrAllocate(LightningWarhead);
	BuildingType::Array.findOrAllocate(PrismType);
	AircraftType::Array.findOrAllocate(V3RocketType);
	AircraftType::Array.findOrAllocate(DMislType);
	AircraftType::Array.findOrAllocate(CMislType);
	TerrainType::Array.findOrAllocate(VeinholeTypeClass);
	allocateList(TerrainType::Array, DefaultMirageDisguises);
}
