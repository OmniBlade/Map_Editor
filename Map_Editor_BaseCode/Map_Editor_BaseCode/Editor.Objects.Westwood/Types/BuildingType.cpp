#include "stdafx.h"
#include "BuildingType.hpp"
#include <iostream>
#include "../../Log.hpp"
#include "../../Editor.FileSystem/INIFile/LineSplitter.hpp"
#include "VehicleType.hpp"
#include "InfantryType.hpp"
#include "OverlayType.hpp"

/* static */ List<BuildingType> BuildingType::Array;

BuildingType::BuildingType(const std::string& id)
:TechnoType(id)
{
}

void BuildingType::loadRules(INIFile* rules)
{
	INISection* rulesSection = rules->getSection(ID);
	if (!rulesSection) return;

	TechnoType::loadRules(rules);

	ToTile = rulesSection->readStringValue("ToTile", ToTile);
	HasSpotlight = rulesSection->readBoolValue("HasSpotlight", HasSpotlight);

	HalfDamageSmokeLocation1_str = rulesSection->readStringValue("HalfDamageSmokeLocation1", HalfDamageSmokeLocation1_str);
	LineSplitter split(HalfDamageSmokeLocation1_str);
	HalfDamageSmokeLocation1.x = split.pop_int();
	HalfDamageSmokeLocation1.y = split.pop_int();
	HalfDamageSmokeLocation1.z = split.pop_int();

	HalfDamageSmokeLocation2_str = rulesSection->readStringValue("HalfDamageSmokeLocation2", HalfDamageSmokeLocation2_str);
	LineSplitter split2(HalfDamageSmokeLocation2_str);
	HalfDamageSmokeLocation2.x = split2.pop_int();
	HalfDamageSmokeLocation2.y = split2.pop_int();
	HalfDamageSmokeLocation2.z = split2.pop_int();

	WaterBound = rulesSection->readBoolValue("WaterBound", WaterBound);
	Powered = rulesSection->readBoolValue("Powered", Powered);
	RefinerySmokeFrames = rulesSection->readIntValue("RefinerySmokeFrames", RefinerySmokeFrames);
	Wall = rulesSection->readBoolValue("Wall", Wall);

	VehicleType::Array.findOrAllocate(rulesSection->readStringValue("FreeUnit"));
	IsPlug = rulesSection->readBoolValue("IsPlug", IsPlug);
	InfantryType::Array.findOrAllocate(rulesSection->readStringValue("SecretInfantry"));
	VehicleType::Array.findOrAllocate(rulesSection->readStringValue("SecretUnit"));
	BuildingType::Array.findOrAllocate(rulesSection->readStringValue("SecretBuilding"));

	Gate = rulesSection->readBoolValue("Gate", Gate);
	LaserFencePost = rulesSection->readBoolValue("LaserFencePost", LaserFencePost);
	LaserFence = rulesSection->readBoolValue("LaserFence", LaserFence);
	FirestormWall = rulesSection->readBoolValue("FirestormWall", FirestormWall);
	PowersUpBuilding = rulesSection->readStringValue("PowersUpBuilding", PowersUpBuilding);
	PowersUpToLevel = rulesSection->readIntValue("PowersUpToLevel", PowersUpToLevel);
	Power = rulesSection->readIntValue("Power", Power);
	ExtraPower = rulesSection->readIntValue("ExtraPower", ExtraPower);

	TurretAnim = rulesSection->readStringValue("TurretAnim", TurretAnim);
	TurretAnimDamaged = rulesSection->readStringValue("TurretAnimDamaged", TurretAnimDamaged);
	TurretAnimGarrisoned = rulesSection->readStringValue("TurretAnimGarrisoned", TurretAnimGarrisoned);
	TurretAnimX = rulesSection->readIntValue("TurretAnimX", TurretAnimX);
	TurretAnimY = rulesSection->readIntValue("TurretAnimY", TurretAnimY);
	TurretAnimZAdjust = rulesSection->readIntValue("TurretAnimZAdjust", TurretAnimZAdjust);
	TurretAnimYSort = rulesSection->readIntValue("TurretAnimYSort", TurretAnimYSort);
	TurretAnimPowered = rulesSection->readBoolValue("TurretAnimPowered", TurretAnimPowered);
	TurretAnimPoweredLight = rulesSection->readBoolValue("TurretAnimPoweredLight", TurretAnimPoweredLight);
	TurretAnimPoweredEffect = rulesSection->readBoolValue("TurretAnimPoweredEffect", TurretAnimPoweredEffect);
	TurretAnimPoweredSpecial = rulesSection->readBoolValue("TurretAnimPoweredSpecial", TurretAnimPoweredSpecial);
	TurretAnimIsVoxel = rulesSection->readBoolValue("TurretAnimIsVoxel", TurretAnimIsVoxel);
	VoxelBarrelFile = rulesSection->readStringValue("VoxelBarrelFile", VoxelBarrelFile);

	VoxelBarrelOffsetToRotatePivotPoint_str = rulesSection->readStringValue("VoxelBarrelOffsetToRotatePivotPoint", VoxelBarrelOffsetToRotatePivotPoint_str);
	LineSplitter split3(VoxelBarrelOffsetToRotatePivotPoint_str);
	VoxelBarrelOffsetToRotatePivotPoint.x = split3.pop_int();
	VoxelBarrelOffsetToRotatePivotPoint.y = split3.pop_int();
	VoxelBarrelOffsetToRotatePivotPoint.z = split3.pop_int();

	VoxelBarrelOffsetToBuildingPivotPoint_str = rulesSection->readStringValue("VoxelBarrelOffsetToBuildingPivotPoint", VoxelBarrelOffsetToBuildingPivotPoint_str);
	LineSplitter split4(VoxelBarrelOffsetToBuildingPivotPoint_str);
	VoxelBarrelOffsetToBuildingPivotPoint.x = split4.pop_int();
	VoxelBarrelOffsetToBuildingPivotPoint.y = split4.pop_int();
	VoxelBarrelOffsetToBuildingPivotPoint.z = split4.pop_int();

	VoxelBarrelOffsetToPitchPivotPoint_str = rulesSection->readStringValue("VoxelBarrelOffsetToPitchPivotPoint", VoxelBarrelOffsetToPitchPivotPoint_str);
	LineSplitter split5(VoxelBarrelOffsetToPitchPivotPoint_str);
	VoxelBarrelOffsetToPitchPivotPoint.x = split5.pop_int();
	VoxelBarrelOffsetToPitchPivotPoint.y = split5.pop_int();
	VoxelBarrelOffsetToPitchPivotPoint.z = split5.pop_int();

	VoxelBarrelOffsetToBarrelEnd_str = rulesSection->readStringValue("VoxelBarrelOffsetToBarrelEnd", VoxelBarrelOffsetToBarrelEnd_str);
	LineSplitter split6(VoxelBarrelOffsetToBarrelEnd_str);
	VoxelBarrelOffsetToBarrelEnd.x = split6.pop_int();
	VoxelBarrelOffsetToBarrelEnd.y = split6.pop_int();
	VoxelBarrelOffsetToBarrelEnd.z = split6.pop_int();
	
	Upgrades = rulesSection->readIntValue("Upgrades", Upgrades);
}

void BuildingType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	TechnoType::loadArt(art);

	Height = artSection->readIntValue("Height", 2);
	OccupyHeight = artSection->readIntValue("OccupyHeight", 2);
	OverlayType::Array.findOrAllocate(artSection->readStringValue("ToOverlay"));
	Foundation; //TODO: implement foundations
	TerrainPalette = artSection->readBoolValue("TerrainPalette", false);
	//Active Anim1
	ActiveAnim = artSection->readStringValue("ActiveAnim", "");
	ActiveAnimDamaged = artSection->readStringValue("ActiveAnimDamaged", "");
	ActiveAnimX = artSection->readIntValue("ActiveAnimX", 0);
	ActiveAnimY = artSection->readIntValue("ActiveAnimY", 0);
	ActiveAnimZAdjust = artSection->readIntValue("ActiveAnimZAdjust", 0);
	ActiveAnimYSort = artSection->readIntValue("ActiveAnimYSort", 0);
	ActiveAnimPowered = artSection->readBoolValue("ActiveAnimPowered", false);
	ActiveAnimPoweredLight = artSection->readBoolValue("ActiveAnimPoweredLight", false);
	ActiveAnimPoweredSpecial = artSection->readBoolValue("ActiveAnimPoweredSpecial", false);
	//Active Anim2
	ActiveAnimTwo = artSection->readStringValue("ActiveAnimTwo", "");
	ActiveAnimTwoDamaged = artSection->readStringValue("ActiveAnimTwoDamaged", "");
	ActiveAnimTwoX = artSection->readIntValue("ActiveAnimTwoX", 0);
	ActiveAnimTwoY = artSection->readIntValue("ActiveAnimTwoY", 0);
	ActiveAnimTwoZAdjust = artSection->readIntValue("ActiveAnimTwoZAdjust", 0);
	ActiveAnimTwoYSort = artSection->readIntValue("ActiveAnimTwoYSort", 0);
	ActiveAnimTwoPowered = artSection->readBoolValue("ActiveAnimTwoPowered", false);
	ActiveAnimTwoPoweredLight = artSection->readBoolValue("ActiveAnimTwoPoweredLight", false);
	ActiveAnimTwoPoweredSpecial = artSection->readBoolValue("ActiveAnimTwoPoweredSpecial", false);
	//Active Anim3
	ActiveAnimThree = artSection->readStringValue("ActiveAnimThree", "");
	ActiveAnimThreeDamaged = artSection->readStringValue("ActiveAnimThreeDamaged", "");
	ActiveAnimThreeX = artSection->readIntValue("ActiveAnimThreeX", 0);
	ActiveAnimThreeY = artSection->readIntValue("ActiveAnimThreeY", 0);
	ActiveAnimThreeZAdjust = artSection->readIntValue("ActiveAnimThreeZAdjust", 0);
	ActiveAnimThreeYSort = artSection->readIntValue("ActiveAnimThreeYSort", 0);
	ActiveAnimThreePowered = artSection->readBoolValue("ActiveAnimThreePowered", false);
	ActiveAnimThreePoweredLight = artSection->readBoolValue("ActiveAnimThreePoweredLight", false);
	ActiveAnimThreePoweredSpecial = artSection->readBoolValue("ActiveAnimThreePoweredSpecial", false);
	//Active Anim4
	ActiveAnimFour = artSection->readStringValue("ActiveAnimFour", "");
	ActiveAnimFourDamaged = artSection->readStringValue("ActiveAnimFourDamaged", "");
	ActiveAnimFourX = artSection->readIntValue("ActiveAnimFourX", 0);
	ActiveAnimFourY = artSection->readIntValue("ActiveAnimFourY", 0);
	ActiveAnimFourZAdjust = artSection->readIntValue("ActiveAnimFourZAdjust", 0);
	ActiveAnimFourYSort = artSection->readIntValue("ActiveAnimFourYSort", 0);
	ActiveAnimFourPowered = artSection->readBoolValue("ActiveAnimFourPowered", false);
	ActiveAnimFourPoweredLight = artSection->readBoolValue("ActiveAnimFourPoweredLight", false);
	ActiveAnimFourPoweredSpecial = artSection->readBoolValue("ActiveAnimFourPoweredSpecial", false);
	
	//Special Anims 1-4
	//TODO: Rework in class?
	//Concept is simple: sizes are all the same and bound to 'Upgrades' key

	//PowerUpAnims;
	//PowerUpDamagedAnims;
	//PowerUpLocXXs;
	//PowerUpLocYYs;
	//PowerUpLocZZs;
	//PowerUpXYSorts;

	Rubble = artSection->readStringValue("Rubble", "");
	BibShape = artSection->readStringValue("BibShape", "");
	ArtImage = artSection->readStringValue("Image", "");
}