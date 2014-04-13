#include "stdafx.h"
#include "TerrainType.hpp"


TerrainType::TerrainType(INISection* _rulesSection, INISection* _artSection)
:ObjectType(_rulesSection, _artSection), artSection(_artSection), rulesSection(_rulesSection)
{

}

void TerrainType::loadRules()
{
	IsVeinhole = rulesSection->readBoolValue("IsVeinHole", false);
	WaterBound = rulesSection->readBoolValue("WaterBound", false);
	SpawnsTiberium = rulesSection->readBoolValue("SpawnsTiberium", false);
	RadarColor = rulesSection->readStringValue("IsVeinHole", "0,0,0");
	IsAnimated = rulesSection->readBoolValue("IsAnimated", false);
	AnimationRate = rulesSection->readIntValue("AnimationRate", 0);
	AnimationProbability = rulesSection->readFloatValue("AnimationProbability", 0.0);
	TemperateOccupationBits = rulesSection->readIntValue("TemperateOccupationBits", 7);
	SnowOccupationBits = rulesSection->readIntValue("SnowOccupationBits", 7);
}

void TerrainType::loadArt()
{
	Foundation = artSection->readStringValue("Foundation", "1x1");
}