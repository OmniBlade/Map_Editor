#pragma once

#include "../Types/AbstractType.hpp"

class General : public AbstractType
{
public:
	General(const std::string& id);
	void loadRules(INIFile* file) override;

	std::string DamageFireTypes = ""; // All anims
	std::string OreTwinkle = "";
	std::string BarrelExplode = "";
	std::string BarrelDebris = "";
	std::string NukeTakeOff = "";
	std::string Wake = "";
	std::string DropPod = "";
	std::string DeadBodies = "";
	std::string MetallicDebris = "";
	std::string BridgeExplosions = "";
	std::string IonBlast = "";
	std::string IonBeam = "";
	std::string WeatherConClouds = "";
	std::string WeatherConBolts = "";
	std::string WeatherConBoltExplosion = "";
	std::string DominatorFirstAnim = "";
	std::string DominatorSecondAnim = "";
	std::string ChronoPlacement = "";
	std::string ChronoBeam = "";
	std::string ChronoBlast = "";
	std::string ChronoBlastDest = "";
	std::string WarpIn = "";
	std::string WarpOut = "";
	std::string WarpAway = "";
	std::string IronCurtainInvokeAnim = "";
	std::string ForceShieldInvokeAnim = "";
	std::string WeaponNullifyAnim = "";
	std::string ChronoSparkle1 = "";
	std::string InfantryExplode = "";
	std::string FlamingInfantry = "";
	std::string InfantryHeadPop = "";
	std::string InfantryNuked = "";
	std::string InfantryVirus = "";
	std::string InfantryBrute = "";
	std::string InfantryMutate = "";
	std::string Behind = "";
	std::string MoveFlash = "";
	std::string Parachute = " ";
	std::string BombParachute = "";
	std::string DropZoneAnim = "";
	std::string EMPulseSparkles = "";
	std::string LargeVisceroid = ""; //Vehicle
	std::string SmallVisceroid = ""; //Vehicle
	std::string DropPodWeapon = ""; //Weapon
	std::string ExplosiveVoxelDebris = ""; // VoxelAnim
	std::string TireVoxelDebris = ""; //VoxelAnim
	std::string ScrapVoxelDebris = ""; //VoxelAnim
	std::string RepairBay = ""; // All buildings
	std::string GDIGateOne = "";
	std::string GDIGateTwo = "";
	std::string NodGateOne = "";
	std::string NodGateTwo = "";
	std::string WallTower = "";
	std::string Shipyard = "";
	std::string GDIPowerPlant = "";
	std::string NodRegularPower = "";
	std::string NodAdvancedPower = "";
	std::string ThirdPowerPlant = "";
	std::string PrerequisiteProcAlternate = ""; //Vehicle
	std::string BaseUnit = ""; //Vehicle
	std::string HarvesterUnit = ""; //Vehicle
	std::string PadAircraft = ""; //Aircraft
	std::string Paratrooper = ""; //Infantry
	std::string SecretInfantry = ""; // Inf
	std::string SecretUnits = ""; // Unit
	std::string SecretBuildings = ""; //Buyild
	std::string AlliedDisguise = "";
	std::string SovietDisguise = "";
	std::string ThirdDisguise = "";
	std::string Engineer = "";
	std::string Technician = "";
	std::string Pilot = "";
	std::string AlliedCrew = "";
	std::string SovietCrew = "";
	std::string ThirdCrew = "";
	std::string AmerParaDropInf = "";
	std::string AllyParaDropInf = "";
	std::string SovParaDropInf = "";
	std::string YuriParaDropInf = "";
	std::string AnimToInfantry = "";
	std::string PrismType = ""; //Building
	std::string V3RocketType = ""; //Air
	std::string DMislType = ""; // Air
	std::string CMislType = ""; // Air
	std::string VeinholeTypeClass = ""; //Terrain
	std::string DefaultMirageDisguises = ""; //Terrain
};

