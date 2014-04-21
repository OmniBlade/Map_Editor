#pragma once

#include "ObjectType.hpp"
#include "../Managers/List.hpp"

class TerrainType : public ObjectType
{
public:
	static List<TerrainType> Array;
	TerrainType(const std::string& id);

	void loadRules(INIFile* rules) override;
	void loadArt(INIFile* rules) override;

//Rules
	bool IsVeinhole = false;
	bool WaterBound = false;
	bool SpawnsTiberium = false;
	bool IsFlammable = false;
	std::string RadarColor = "0,0,0";
	bool IsAnimated = false;
	int AnimationRate = 0;
	float AnimationProbability = 0.0f;
	int TemperateOccupationBits = 7;
	int SnowOccupationBits = 7;

//Art
	std::string Foundation;
};

