#include "stdafx.h"
#include "TerrainType.hpp"
#include "../../Log.hpp"

/* static */ WWList<TerrainType> TerrainType::Array;

TerrainType::TerrainType(const std::string& id)
:ObjectType(id)
{
}

void TerrainType::loadRules(INIFile* rules)
{
	INISection* rulesSection = rules->getSection(ID);
	if (!rulesSection) return;

	ObjectType::loadRules(rules);

	rulesSection->readBoolValue("IsVeinHole", IsVeinhole);
	rulesSection->readBoolValue("WaterBound", WaterBound);
	rulesSection->readBoolValue("SpawnsTiberium", SpawnsTiberium);
	rulesSection->readStringValue("RadarColor", RadarColor);
	rulesSection->readBoolValue("IsAnimated", IsAnimated);
	rulesSection->readIntValue("AnimationRate", AnimationRate);
	rulesSection->readFloatValue("AnimationProbability", AnimationProbability);
	rulesSection->readIntValue("TemperateOccupationBits", TemperateOccupationBits);
	rulesSection->readIntValue("SnowOccupationBits", SnowOccupationBits);
}

void TerrainType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	ObjectType::loadArt(art);

	artSection->readStringValue("Foundation", Foundation);
}