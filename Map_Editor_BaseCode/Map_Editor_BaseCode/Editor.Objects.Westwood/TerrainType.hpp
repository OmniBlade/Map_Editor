#pragma once

#include "ObjectType.hpp"

class TerrainType : public ObjectType
{
public:
	TerrainType(INISection* _rulesSection, INISection* _artSection);

	void loadRules() override;
	void loadArt() override;

//Rules
	bool IsVeinhole;
	bool WaterBound;
	bool SpawnsTiberium;
	bool IsFlammable;
	std::string RadarColor;
	bool IsAnimated;
	int AnimationRate;
	float AnimationProbability;
	int TemperateOccupationBits;
	int SnowOccupationBits;

//Art
	std::string Foundation;

protected:
	INISection* rulesSection;
	INISection* artSection;
};

