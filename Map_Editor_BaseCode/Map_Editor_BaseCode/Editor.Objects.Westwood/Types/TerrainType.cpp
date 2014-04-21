#include "stdafx.h"
#include "TerrainType.hpp"
#include "../../Log.hpp"

/* static */ List<TerrainType> TerrainType::Array;

TerrainType::TerrainType(const std::string& id)
:ObjectType(id)
{
}

void TerrainType::loadRules(INIFile* rules)
{
	INISection* rulesSection = rules->getSection(ID);
	if (!rulesSection) return;

	ObjectType::loadRules(rules);

	IsVeinhole = rulesSection->readBoolValue("IsVeinHole", IsVeinhole);
	WaterBound = rulesSection->readBoolValue("WaterBound", WaterBound);
	SpawnsTiberium = rulesSection->readBoolValue("SpawnsTiberium", SpawnsTiberium);
	RadarColor = rulesSection->readStringValue("RadarColor", RadarColor);
	IsAnimated = rulesSection->readBoolValue("IsAnimated", IsAnimated);
	AnimationRate = rulesSection->readIntValue("AnimationRate", AnimationRate);
	AnimationProbability = rulesSection->readFloatValue("AnimationProbability", AnimationProbability);
	TemperateOccupationBits = rulesSection->readIntValue("TemperateOccupationBits", TemperateOccupationBits);
	SnowOccupationBits = rulesSection->readIntValue("SnowOccupationBits", SnowOccupationBits);
}

void TerrainType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	ObjectType::loadArt(art);

	Foundation = artSection->readStringValue("Foundation", "1x1");
}