#pragma once

#include <string>
#include <vector>
#include "../Vector3D.hpp"
#include "Foundation.hpp"
#include "TechnoType.hpp"
#include "../Managers/WWList.hpp"

class BuildingType : public TechnoType
{
public:
	static WWList<BuildingType> Array;

	BuildingType(const std::string& id);

	void loadRules(INIFile* rules) override;
	void loadArt(INIFile* art) override;

//--Rules flags
	std::string FreeUnit, SecretInfantry, SecretUnit, SecretBuilding;


	std::string ToTile = "";
	bool HasSpotlight = false;
	std::string HalfDamageSmokeLocation1_str = "0,0,0";
	std::string HalfDamageSmokeLocation2_str = "0,0,0";
	Vector3D HalfDamageSmokeLocation1; //TODO: Gotta rework that in 3DVector
	Vector3D HalfDamageSmokeLocation2; //TODO: Gotta rework that in 3DVector
	bool WaterBound = false;
	bool Powered = false;
	int RefinerySmokeFrames = 25;
	bool Wall = false;
	bool IsPlug = false;
	bool Gate = false;
	bool LaserFencePost = false;
	bool LaserFence = false;
	bool FirestormWall = false;
	std::string PowersUpBuilding = "";
	int PowersUpToLevel = -1;
	int Power = 0;
	int ExtraPower = 0;
	std::string TurretAnim = "";
	std::string TurretAnimDamaged = "";
	std::string TurretAnimGarrisoned = "";
	int TurretAnimX = 0;
	int TurretAnimY = 0;
	int TurretAnimZAdjust = 0;
	int TurretAnimYSort = 0;
	bool TurretAnimPowered = false;
	bool TurretAnimPoweredLight = false;
	bool TurretAnimPoweredEffect = false;
	bool TurretAnimPoweredSpecial = false;
	bool TurretAnimIsVoxel = false;
	std::string VoxelBarrelFile = "";
	std::string VoxelBarrelOffsetToPitchPivotPoint_str = "0,0,0";
	std::string VoxelBarrelOffsetToRotatePivotPoint_str = "0,0,0";
	std::string VoxelBarrelOffsetToBuildingPivotPoint_str = "0,0,0";
	std::string VoxelBarrelOffsetToBarrelEnd_str = "0,0,0";
	Vector3D VoxelBarrelOffsetToPitchPivotPoint;
	Vector3D VoxelBarrelOffsetToRotatePivotPoint;
	Vector3D VoxelBarrelOffsetToBuildingPivotPoint;
	Vector3D VoxelBarrelOffsetToBarrelEnd;
	int Upgrades = 0;

//--Art flags
	int Height = 2;
	int OccupyHeight = 2;
	Foundation Foundation;
	std::string ToOverlay;
	bool TerrainPalette;
	std::string ActiveAnim;
	std::string ActiveAnimDamaged;
	int ActiveAnimX;
	int ActiveAnimY;
	int ActiveAnimZAdjust;
	int ActiveAnimYSort;
	bool ActiveAnimPowered;
	bool ActiveAnimPoweredLight;
	bool ActiveAnimPoweredSpecial;
	std::string ActiveAnimTwo;
	std::string ActiveAnimTwoDamaged;
	int ActiveAnimTwoX;
	int ActiveAnimTwoY;
	int ActiveAnimTwoZAdjust;
	int ActiveAnimTwoYSort;
	bool ActiveAnimTwoPowered;
	bool ActiveAnimTwoPoweredLight;
	bool ActiveAnimTwoPoweredSpecial;
	std::string ActiveAnimThree;
	std::string ActiveAnimThreeDamaged;
	int ActiveAnimThreeX;
	int ActiveAnimThreeY;
	int ActiveAnimThreeZAdjust;
	int ActiveAnimThreeYSort;
	bool ActiveAnimThreePowered;
	bool ActiveAnimThreePoweredLight;
	bool ActiveAnimThreePoweredSpecial;
	std::string ActiveAnimFour;
	std::string ActiveAnimFourDamaged;
	int ActiveAnimFourX;
	int ActiveAnimFourY;
	int ActiveAnimFourZAdjust;
	int ActiveAnimFourYSort;
	bool ActiveAnimFourPowered;
	bool ActiveAnimFourPoweredLight;
	bool ActiveAnimFourPoweredSpecial;
	//Special Anims 1-4
	//TODO: Rework in class?
	std::vector<std::string> PowerUpAnims;
	std::vector<std::string> PowerUpDamagedAnims;
	std::vector<int> PowerUpLocXXs;
	std::vector<int> PowerUpLocYYs;
	std::vector<int> PowerUpLocZZs;
	std::vector<int> PowerUpXYSorts;
	std::string Rubble;
	std::string BibShape;
	std::string ArtImage;
};

