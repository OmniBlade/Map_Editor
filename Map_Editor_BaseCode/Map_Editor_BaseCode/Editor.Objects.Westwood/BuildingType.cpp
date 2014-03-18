#include "stdafx.h"
#include "BuildingType.hpp"
#include "../Editor.FileSystem/INIFile/LineSplitter.hpp"


BuildingType::BuildingType(INISection* _rulesSection, INISection* _artSection)
:TechnoType(_rulesSection, _artSection), artSection(_artSection), rulesSection(_rulesSection)
{
}

void BuildingType::loadRules()
{
	ToTile = rulesSection->readStringValue("ToTile", "");
	HasSpotlight = rulesSection->readBoolValue("HasSpotlight", false);

	LineSplitter split(rulesSection->readStringValue("HalfDamageSmokeLocation1", "0,0,0"));
	HalfDamageSmokeLocation1.x = split.pop_int();
	HalfDamageSmokeLocation1.y = split.pop_int();
	HalfDamageSmokeLocation1.z = split.pop_int();
	LineSplitter split2(rulesSection->readStringValue("HalfDamageSmokeLocation2", "0,0,0"));
	HalfDamageSmokeLocation2.x = split2.pop_int();
	HalfDamageSmokeLocation2.y = split2.pop_int();
	HalfDamageSmokeLocation2.z = split2.pop_int();

	WaterBound = rulesSection->readBoolValue("WaterBound", false);
	Powered = rulesSection->readBoolValue("Powered", false);
	RefinerySmokeFrames = rulesSection->readIntValue("RefinerySmokeFrames", 25);
	Wall = rulesSection->readBoolValue("Wall", false);
	IsPlug = rulesSection->readBoolValue("IsPlug", false);
	Gate = rulesSection->readBoolValue("Gate", false);
	LaserFencePost = rulesSection->readBoolValue("LaserFencePost", false);
	LaserFence = rulesSection->readBoolValue("LaserFence", false);
	FirestormWall = rulesSection->readBoolValue("FirestormWall", false);
	PowersUpBuilding = rulesSection->readStringValue("PowersUpBuilding", "");
	PowersUpToLevel = rulesSection->readIntValue("PowersUpToLevel", -1);
	Power = rulesSection->readIntValue("Power", 0);
	ExtraPower = rulesSection->readIntValue("ExtraPower", 0);

	TurretAnim = rulesSection->readStringValue("TurretAnim", "");
	TurretAnimDamaged = rulesSection->readStringValue("TurretAnimDamaged", "");
	TurretAnimGarrisoned = rulesSection->readStringValue("TurretAnimGarrisoned", "");
	TurretAnimX = rulesSection->readIntValue("TurretAnimX", 0);
	TurretAnimY = rulesSection->readIntValue("TurretAnimY", 0);
	TurretAnimZAdjust = rulesSection->readIntValue("TurretAnimZAdjust", 0);
	TurretAnimYSort = rulesSection->readIntValue("TurretAnimYSort", 0);
	TurretAnimPowered = rulesSection->readBoolValue("TurretAnimPowered", false);
	TurretAnimPoweredLight = rulesSection->readBoolValue("TurretAnimPoweredLight", false);
	TurretAnimPoweredEffect = rulesSection->readBoolValue("TurretAnimPoweredEffect", false);
	TurretAnimPoweredSpecial = rulesSection->readBoolValue("TurretAnimPoweredSpecial", false);
	TurretAnimIsVoxel = rulesSection->readBoolValue("TurretAnimIsVoxel", false);
	VoxelBarrelFile = rulesSection->readStringValue("VoxelBarrelFile", "");

	LineSplitter split3(rulesSection->readStringValue("VoxelBarrelOffsetToRotatePivotPoint", "0,0,0"));
	VoxelBarrelOffsetToRotatePivotPoint.x = split3.pop_int();
	VoxelBarrelOffsetToRotatePivotPoint.y = split3.pop_int();
	VoxelBarrelOffsetToRotatePivotPoint.z = split3.pop_int();
	LineSplitter split4(rulesSection->readStringValue("VoxelBarrelOffsetToBuildingPivotPoint", "0,0,0"));
	VoxelBarrelOffsetToBuildingPivotPoint.x = split4.pop_int();
	VoxelBarrelOffsetToBuildingPivotPoint.y = split4.pop_int();
	VoxelBarrelOffsetToBuildingPivotPoint.z = split4.pop_int();
	LineSplitter split5(rulesSection->readStringValue("VoxelBarrelOffsetToPitchPivotPoint", "0,0,0"));
	VoxelBarrelOffsetToPitchPivotPoint.x = split5.pop_int();
	VoxelBarrelOffsetToPitchPivotPoint.y = split5.pop_int();
	VoxelBarrelOffsetToPitchPivotPoint.z = split5.pop_int();
	LineSplitter split6(rulesSection->readStringValue("VoxelBarrelOffsetToBarrelEnd", "0,0,0"));
	VoxelBarrelOffsetToBarrelEnd.x = split6.pop_int();
	VoxelBarrelOffsetToBarrelEnd.y = split6.pop_int();
	VoxelBarrelOffsetToBarrelEnd.z = split6.pop_int();
	
	Upgrades = rulesSection->readIntValue("Upgrades", 0);
}

void BuildingType::loadArt()
{
	Height = artSection->readIntValue("Height", 2);
	OccupyHeight = artSection->readIntValue("OccupyHeight", 2);
	ToOverlay = artSection->readStringValue("ToOverlay", "0");
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