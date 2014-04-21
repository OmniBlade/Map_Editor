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
	allocateList(Animation::Array, section->readStringValue("DamageFireTypes", DamageFireTypes));
	allocateList(Animation::Array, section->readStringValue("OreTwinkle", OreTwinkle));
	allocateList(Animation::Array, section->readStringValue("BarrelExplode", BarrelExplode));
	allocateList(Animation::Array, section->readStringValue("NukeTakeOff", NukeTakeOff));
	allocateList(Animation::Array, section->readStringValue("Wake", Wake));
	allocateList(Animation::Array, section->readStringValue("DropPod", DropPod));
	allocateList(Animation::Array, section->readStringValue("DeadBodies", DeadBodies));
	allocateList(Animation::Array, section->readStringValue("MetallicDebris", MetallicDebris));
	allocateList(Animation::Array, section->readStringValue("BridgeExplosions", BridgeExplosions));
	allocateList(Animation::Array, section->readStringValue("IonBlast", IonBlast));
	allocateList(Animation::Array, section->readStringValue("WeatherConClouds", WeatherConClouds));
	//allocateList(Animation::Array, section->readStringValue("WeatherConBolts", WeatherConBolts));
	allocateList(Animation::Array, section->readStringValue("WeatherConBoltExplosion", WeatherConBoltExplosion));
	allocateList(WarheadType::Array, section->readStringValue("DominatorWarhead"));
	allocateList(Animation::Array, section->readStringValue("DominatorFirstAnim", DominatorFirstAnim));
	allocateList(Animation::Array, section->readStringValue("DominatorSecondAnim", DominatorSecondAnim));
	allocateList(Animation::Array, section->readStringValue("ChronoPlacement", ChronoPlacement));
	allocateList(Animation::Array, section->readStringValue("ChronoBeam", ChronoBeam));
	allocateList(Animation::Array, section->readStringValue("ChronoBlast", ChronoBlast));
	allocateList(Animation::Array, section->readStringValue("ChronoBlastDest", ChronoBlastDest));
	allocateList(Animation::Array, section->readStringValue("WarpIn", WarpIn));
	allocateList(Animation::Array, section->readStringValue("WarpOut", WarpOut));
	allocateList(Animation::Array, section->readStringValue("WarpAway", WarpAway));
	allocateList(Animation::Array, section->readStringValue("IronCurtainInvokeAnim", IronCurtainInvokeAnim));
	allocateList(Animation::Array, section->readStringValue("ForceShieldInvokeAnim", ForceShieldInvokeAnim));
	allocateList(Animation::Array, section->readStringValue("WeaponNullifyAnim", WeaponNullifyAnim));
	allocateList(Animation::Array, section->readStringValue("ChronoSparkle1", ChronoSparkle1));
	allocateList(Animation::Array, section->readStringValue("InfantryExplode", InfantryExplode));
	allocateList(Animation::Array, section->readStringValue("FlamingInfantry", FlamingInfantry));
	allocateList(Animation::Array, section->readStringValue("InfantryHeadPop", InfantryHeadPop));
	allocateList(Animation::Array, section->readStringValue("InfantryNuked", InfantryNuked));
	allocateList(Animation::Array, section->readStringValue("InfantryVirus", InfantryVirus));
	allocateList(Animation::Array, section->readStringValue("InfantryBrute", InfantryBrute));
	allocateList(Animation::Array, section->readStringValue("InfantryMutate", InfantryMutate));
	allocateList(Animation::Array, section->readStringValue("Behind", Behind));
	allocateList(Animation::Array, section->readStringValue("MoveFlash", MoveFlash));
	allocateList(Animation::Array, section->readStringValue("Parachute", Parachute));
	allocateList(Animation::Array, section->readStringValue("BombParachute", BombParachute));
	allocateList(Animation::Array, section->readStringValue("DropZoneAnim", DropZoneAnim));
	allocateList(Animation::Array, section->readStringValue("EMPulseSparkles", EMPulseSparkles));
	allocateList(VehicleType::Array, section->readStringValue("LargeVisceroid", LargeVisceroid));
	allocateList(VehicleType::Array, section->readStringValue("SmallVisceroid", SmallVisceroid));
	allocateList(WeaponType::Array, section->readStringValue("DropPodWeapon", DropPodWeapon));
	allocateList(VoxelAnimType::Array, section->readStringValue("ExplosiveVoxelDebris", ExplosiveVoxelDebris));
	allocateList(VoxelAnimType::Array, section->readStringValue("TireVoxelDebris", TireVoxelDebris));
	allocateList(VoxelAnimType::Array, section->readStringValue("ScrapVoxelDebris", ScrapVoxelDebris));
	allocateList(BuildingType::Array, section->readStringValue("RepairBay", RepairBay));
	allocateList(BuildingType::Array, section->readStringValue("GDIGateOne", GDIGateOne));
	allocateList(BuildingType::Array, section->readStringValue("GDIGateTwo", GDIGateTwo));
	allocateList(BuildingType::Array, section->readStringValue("NodGateOne", NodGateOne));
	allocateList(BuildingType::Array, section->readStringValue("NodGateTwo", NodGateTwo));
	allocateList(BuildingType::Array, section->readStringValue("WallTower", WallTower));
	allocateList(BuildingType::Array, section->readStringValue("Shipyard", Shipyard));
	allocateList(BuildingType::Array, section->readStringValue("GDIPowerPlant", GDIPowerPlant));
	allocateList(BuildingType::Array, section->readStringValue("NodRegularPower", NodRegularPower));
	allocateList(BuildingType::Array, section->readStringValue("NodAdvancedPower", NodAdvancedPower));
	allocateList(BuildingType::Array, section->readStringValue("ThirdPowerPlant", ThirdPowerPlant));
	allocateList(VehicleType::Array, section->readStringValue("PrerequisiteProcAlternate", PrerequisiteProcAlternate));
	allocateList(VehicleType::Array, section->readStringValue("BaseUnit", BaseUnit));
	allocateList(VehicleType::Array, section->readStringValue("HarvesterUnit", HarvesterUnit));
	allocateList(AircraftType::Array, section->readStringValue("PadAircraft", PadAircraft));
	allocateList(Animation::Array, section->readStringValue("Paratrooper", Paratrooper));
	allocateList(InfantryType::Array, section->readStringValue("SecretInfantry", SecretInfantry));
	allocateList(VehicleType::Array, section->readStringValue("SecretUnits", SecretUnits));
	allocateList(BuildingType::Array, section->readStringValue("SecretBuildings", SecretBuildings));
	allocateList(InfantryType::Array, section->readStringValue("AlliedDisguise", AlliedDisguise));
	allocateList(InfantryType::Array, section->readStringValue("SovietDisguise", SovietDisguise));
	allocateList(InfantryType::Array, section->readStringValue("ThirdDisguise", ThirdDisguise));
	allocateList(InfantryType::Array, section->readStringValue("Engineer", Engineer));
	allocateList(InfantryType::Array, section->readStringValue("Technician", Technician));
	allocateList(InfantryType::Array, section->readStringValue("Pilot", Pilot));
	allocateList(InfantryType::Array, section->readStringValue("AlliedCrew", AlliedCrew));
	allocateList(InfantryType::Array, section->readStringValue("SovietCrew", SovietCrew));
	allocateList(InfantryType::Array, section->readStringValue("ThirdCrew", ThirdCrew));
	allocateList(InfantryType::Array, section->readStringValue("AmerParaDropInf", AmerParaDropInf));
	allocateList(InfantryType::Array, section->readStringValue("AllyParaDropInf", AllyParaDropInf));
	allocateList(InfantryType::Array, section->readStringValue("SovParaDropInf", SovParaDropInf));
	allocateList(InfantryType::Array, section->readStringValue("YuriParaDropInf", YuriParaDropInf));
	allocateList(InfantryType::Array, section->readStringValue("AnimToInfantry", AnimToInfantry));
	allocateList(WarheadType::Array, section->readStringValue("LightningWarhead"));
	allocateList(BuildingType::Array, section->readStringValue("PrismType", PrismType));
	allocateList(AircraftType::Array, section->readStringValue("V3RocketType", V3RocketType));
	allocateList(AircraftType::Array, section->readStringValue("DMislType", DMislType));
	allocateList(AircraftType::Array, section->readStringValue("CMislType", CMislType));
	allocateList(TerrainType::Array, section->readStringValue("VeinholeTypeClass", VeinholeTypeClass));
	allocateList(TerrainType::Array, section->readStringValue("DefaultMirageDisguises", DefaultMirageDisguises));
}
