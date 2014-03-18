#pragma once

#include <string>
#include <vector>
#include "Vector3D.hpp"
#include "Foundation.hpp"
#include "TechnoType.hpp"
#include "../Editor.FileSystem/INIFile/INISection.hpp"

class BuildingType : public TechnoType
{
public:
	BuildingType(INISection* _rulesSection, INISection* _artSection);

	void loadRules() override;
	void loadArt() override;

//--Rules flags
	std::string ToTile;
	bool HasSpotlight;
	Vector3D HalfDamageSmokeLocation1; //TODO: Gotta rework that in 3DVector
	Vector3D HalfDamageSmokeLocation2; //TODO: Gotta rework that in 3DVector
	bool WaterBound;
	bool Powered;
	int RefinerySmokeFrames;
	bool Wall;
	bool IsPlug;
	bool Gate;
	bool LaserFencePost;
	bool LaserFence;
	bool FirestormWall;
	std::string PowersUpBuilding;
	int PowersUpToLevel;
	int Power;
	int ExtraPower;
	std::string TurretAnim;
	std::string TurretAnimDamaged;
	std::string TurretAnimGarrisoned;
	int TurretAnimX;
	int TurretAnimY;
	int TurretAnimZAdjust;
	int TurretAnimYSort;
	bool TurretAnimPowered;
	bool TurretAnimPoweredLight;
	bool TurretAnimPoweredEffect;
	bool TurretAnimPoweredSpecial;
	bool TurretAnimIsVoxel;
	std::string VoxelBarrelFile;
	Vector3D VoxelBarrelOffsetToPitchPivotPoint;
	Vector3D VoxelBarrelOffsetToRotatePivotPoint;
	Vector3D VoxelBarrelOffsetToBuildingPivotPoint;
	Vector3D VoxelBarrelOffsetToBarrelEnd;
	int Upgrades;

//--Art flags
	int Height;
	int OccupyHeight;
	std::string ToOverlay;
	Foundation Foundation;
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

protected:
	INISection* rulesSection = nullptr;
	INISection* artSection = nullptr;
};

