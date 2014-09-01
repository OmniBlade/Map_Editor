#include "stdafx.h"
#include "BuildingType.hpp"
#include <iostream>
#include "../../Log.hpp"
#include "../../Editor.FileSystem/INIFile/LineSplitter.hpp"
#include "VehicleType.hpp"
#include "InfantryType.hpp"
#include "OverlayType.hpp"

/* static */ WWList<BuildingType> BuildingType::Array;

BuildingType::BuildingType(const std::string& id)
:TechnoType(id)
{
}

void BuildingType::loadRules(INIFile* rules)
{
	INISection* rulesSection = rules->getSection(ID);
	if (!rulesSection) return;

	TechnoType::loadRules(rules);

	rulesSection->readStringValue("ToTile", ToTile, ToTile.c_str());
	rulesSection->readBoolValue("HasSpotlight", HasSpotlight, HasSpotlight);

	rulesSection->readStringValue("HalfDamageSmokeLocation1", HalfDamageSmokeLocation1_str, HalfDamageSmokeLocation1_str.c_str());
	LineSplitter split(HalfDamageSmokeLocation1_str);
	HalfDamageSmokeLocation1.x = split.pop_int();
	HalfDamageSmokeLocation1.y = split.pop_int();
	HalfDamageSmokeLocation1.z = split.pop_int();

	rulesSection->readStringValue("HalfDamageSmokeLocation2", HalfDamageSmokeLocation2_str, HalfDamageSmokeLocation2_str.c_str());
	LineSplitter split2(HalfDamageSmokeLocation2_str);
	HalfDamageSmokeLocation2.x = split2.pop_int();
	HalfDamageSmokeLocation2.y = split2.pop_int();
	HalfDamageSmokeLocation2.z = split2.pop_int();

	rulesSection->readBoolValue("WaterBound", WaterBound, WaterBound);
	rulesSection->readBoolValue("Powered", Powered, Powered);
	rulesSection->readIntValue("RefinerySmokeFrames", RefinerySmokeFrames, RefinerySmokeFrames);
	rulesSection->readBoolValue("Wall", Wall, Wall);

	VehicleType::Array.findOrAllocate(FreeUnit);
	rulesSection->readBoolValue("IsPlug", IsPlug);
	InfantryType::Array.findOrAllocate(SecretInfantry);
	VehicleType::Array.findOrAllocate(SecretUnit);
	BuildingType::Array.findOrAllocate(SecretBuilding);

	rulesSection->readBoolValue("Gate", Gate);
	rulesSection->readBoolValue("LaserFencePost", LaserFencePost);
	rulesSection->readBoolValue("LaserFence", LaserFence);
	rulesSection->readBoolValue("FirestormWall", FirestormWall);
	rulesSection->readStringValue("PowersUpBuilding", PowersUpBuilding);
	rulesSection->readIntValue("PowersUpToLevel", PowersUpToLevel);
	rulesSection->readIntValue("Power", Power);
	rulesSection->readIntValue("ExtraPower", ExtraPower);

	rulesSection->readStringValue("TurretAnim", TurretAnim);
	rulesSection->readStringValue("TurretAnimDamaged", TurretAnimDamaged);
	rulesSection->readStringValue("TurretAnimGarrisoned", TurretAnimGarrisoned);
	rulesSection->readIntValue("TurretAnimX", TurretAnimX);
	rulesSection->readIntValue("TurretAnimY", TurretAnimY);
	rulesSection->readIntValue("TurretAnimZAdjust", TurretAnimZAdjust);
	rulesSection->readIntValue("TurretAnimYSort", TurretAnimYSort);
	rulesSection->readBoolValue("TurretAnimPowered", TurretAnimPowered);
	rulesSection->readBoolValue("TurretAnimPoweredLight", TurretAnimPoweredLight);
	rulesSection->readBoolValue("TurretAnimPoweredEffect", TurretAnimPoweredEffect);
	rulesSection->readBoolValue("TurretAnimPoweredSpecial", TurretAnimPoweredSpecial);
	rulesSection->readBoolValue("TurretAnimIsVoxel", TurretAnimIsVoxel);
	rulesSection->readStringValue("VoxelBarrelFile", VoxelBarrelFile);

	rulesSection->readStringValue("VoxelBarrelOffsetToRotatePivotPoint", VoxelBarrelOffsetToRotatePivotPoint_str);
	LineSplitter split3(VoxelBarrelOffsetToRotatePivotPoint_str);
	VoxelBarrelOffsetToRotatePivotPoint.x = split3.pop_int();
	VoxelBarrelOffsetToRotatePivotPoint.y = split3.pop_int();
	VoxelBarrelOffsetToRotatePivotPoint.z = split3.pop_int();

	rulesSection->readStringValue("VoxelBarrelOffsetToBuildingPivotPoint", VoxelBarrelOffsetToBuildingPivotPoint_str);
	LineSplitter split4(VoxelBarrelOffsetToBuildingPivotPoint_str);
	VoxelBarrelOffsetToBuildingPivotPoint.x = split4.pop_int();
	VoxelBarrelOffsetToBuildingPivotPoint.y = split4.pop_int();
	VoxelBarrelOffsetToBuildingPivotPoint.z = split4.pop_int();

	rulesSection->readStringValue("VoxelBarrelOffsetToPitchPivotPoint", VoxelBarrelOffsetToPitchPivotPoint_str);
	LineSplitter split5(VoxelBarrelOffsetToPitchPivotPoint_str);
	VoxelBarrelOffsetToPitchPivotPoint.x = split5.pop_int();
	VoxelBarrelOffsetToPitchPivotPoint.y = split5.pop_int();
	VoxelBarrelOffsetToPitchPivotPoint.z = split5.pop_int();

	rulesSection->readStringValue("VoxelBarrelOffsetToBarrelEnd", VoxelBarrelOffsetToBarrelEnd_str);
	LineSplitter split6(VoxelBarrelOffsetToBarrelEnd_str);
	VoxelBarrelOffsetToBarrelEnd.x = split6.pop_int();
	VoxelBarrelOffsetToBarrelEnd.y = split6.pop_int();
	VoxelBarrelOffsetToBarrelEnd.z = split6.pop_int();
	
	rulesSection->readIntValue("Upgrades", Upgrades, Upgrades);
}

void BuildingType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	TechnoType::loadArt(art);

	artSection->readIntValue("Height", Height);
	artSection->readIntValue("OccupyHeight", OccupyHeight);
	artSection->readStringValue("ToOverlay", ToOverlay);
	OverlayType::Array.findOrAllocate(ToOverlay);
	Foundation; //TODO: implement foundations
	artSection->readBoolValue("TerrainPalette", TerrainPalette);
	//Active Anim1
	artSection->readStringValue("ActiveAnim", ActiveAnim);
	artSection->readStringValue("ActiveAnimDamaged", ActiveAnimDamaged);
	artSection->readIntValue("ActiveAnimX", ActiveAnimX);
	artSection->readIntValue("ActiveAnimY", ActiveAnimY);
	artSection->readIntValue("ActiveAnimZAdjust", ActiveAnimZAdjust);
	artSection->readIntValue("ActiveAnimYSort", ActiveAnimYSort);
	artSection->readBoolValue("ActiveAnimPowered", ActiveAnimPowered);
	artSection->readBoolValue("ActiveAnimPoweredLight", ActiveAnimPoweredLight);
	artSection->readBoolValue("ActiveAnimPoweredSpecial", ActiveAnimPoweredSpecial);
	//Active Anim2
	artSection->readStringValue("ActiveAnimTwo", ActiveAnimTwo);
	artSection->readStringValue("ActiveAnimTwoDamaged", ActiveAnimTwoDamaged);
	artSection->readIntValue("ActiveAnimTwoX", ActiveAnimTwoX);
	artSection->readIntValue("ActiveAnimTwoY", ActiveAnimTwoY);
	artSection->readIntValue("ActiveAnimTwoZAdjust", ActiveAnimTwoZAdjust);
	artSection->readIntValue("ActiveAnimTwoYSort", ActiveAnimTwoYSort);
	artSection->readBoolValue("ActiveAnimTwoPowered", ActiveAnimTwoPowered);
	artSection->readBoolValue("ActiveAnimTwoPoweredLight", ActiveAnimTwoPoweredLight);
	artSection->readBoolValue("ActiveAnimTwoPoweredSpecial", ActiveAnimTwoPoweredSpecial);
	//Active Anim3
	artSection->readStringValue("ActiveAnimThree", ActiveAnimThree);
	artSection->readStringValue("ActiveAnimThreeDamaged", ActiveAnimThreeDamaged);
	artSection->readIntValue("ActiveAnimThreeX", ActiveAnimThreeX);
	artSection->readIntValue("ActiveAnimThreeY", ActiveAnimThreeY);
	artSection->readIntValue("ActiveAnimThreeZAdjust", ActiveAnimThreeZAdjust);
	artSection->readIntValue("ActiveAnimThreeYSort", ActiveAnimThreeYSort);
	artSection->readBoolValue("ActiveAnimThreePowered", ActiveAnimThreePowered);
	artSection->readBoolValue("ActiveAnimThreePoweredLight", ActiveAnimThreePoweredLight);
	artSection->readBoolValue("ActiveAnimThreePoweredSpecial", ActiveAnimThreePoweredSpecial);
	//Active Anim4
	artSection->readStringValue("ActiveAnimFour", ActiveAnimFour);
	artSection->readStringValue("ActiveAnimFourDamaged", ActiveAnimFourDamaged);
	artSection->readIntValue("ActiveAnimFourX", ActiveAnimFourX);
	artSection->readIntValue("ActiveAnimFourY", ActiveAnimFourY);
	artSection->readIntValue("ActiveAnimFourZAdjust", ActiveAnimFourZAdjust);
	artSection->readIntValue("ActiveAnimFourYSort", ActiveAnimFourYSort);
	artSection->readBoolValue("ActiveAnimFourPowered", ActiveAnimFourPowered);
	artSection->readBoolValue("ActiveAnimFourPoweredLight", ActiveAnimFourPoweredLight);
	artSection->readBoolValue("ActiveAnimFourPoweredSpecial", ActiveAnimFourPoweredSpecial);
	
	//Special Anims 1-4
	//TODO: Rework in class?
	//Concept is simple: sizes are all the same and bound to 'Upgrades' key

	//PowerUpAnims;
	//PowerUpDamagedAnims;
	//PowerUpLocXXs;
	//PowerUpLocYYs;
	//PowerUpLocZZs;
	//PowerUpXYSorts;

	artSection->readStringValue("Rubble", Rubble);
	artSection->readStringValue("BibShape", BibShape);
	artSection->readStringValue("Image", ArtImage);
}