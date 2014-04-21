#include "stdafx.h"
#include "Animation.hpp"
#include "../../Log.hpp"
#include "WarheadType.hpp"
#include "ParticleType.hpp"
#include "OverlayType.hpp"

/* static */ List<Animation> Animation::Array;

Animation::Animation(const std::string& id)
:ObjectType(id)
{
}

void Animation::loadRules(INIFile* rules)
{
	INISection* rulesSection = rules->getSection(ID);
	if (!rulesSection) return;

	ObjectType::loadRules(rules);
}

void Animation::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	ObjectType::loadArt(art);

	Animation::Array.findOrAllocate(artSection->readStringValue("Next"));
	Animation::Array.findOrAllocate(artSection->readStringValue("Spawns"));
	OverlayType::Array.findOrAllocate(artSection->readStringValue("TiberiumSpawnType"));
	Animation::Array.findOrAllocate(artSection->readStringValue("BounceAnim"));
	Animation::Array.findOrAllocate(artSection->readStringValue("ExpireAnim"));
	Animation::Array.findOrAllocate(artSection->readStringValue("TrailerAnim"));
	WarheadType::Array.findOrAllocate(artSection->readStringValue("Warhead"));
	ParticleType::Array.findOrAllocate(artSection->readStringValue("SpawnsParticle"));

	Shadow = artSection->readBoolValue("Shadow", Shadow);
	AltPalette = artSection->readBoolValue("AltPalette", AltPalette);
	Flat = artSection->readBoolValue("Flat", Flat);
	Normalized = artSection->readBoolValue("Normalized", Normalized);
	Translucent = artSection->readBoolValue("Translucent", Translucent);
	Scorch = artSection->readBoolValue("Scorch", Scorch);
	Crater = artSection->readBoolValue("Crater", Crater);
	ForceBigCraters = artSection->readBoolValue("ForceBigCraters", ForceBigCraters);
	Start = artSection->readIntValue("Start", Start);
	End = artSection->readIntValue("End", End);
	LoopStart = artSection->readIntValue("LoopStart", LoopStart);
	LoopEnd = artSection->readIntValue("LoopEnd", LoopEnd);
	LoopCount = artSection->readIntValue("LoopCount", LoopCount);
	Next = artSection->readStringValue("Next", Next);
	Translucency = artSection->readIntValue("Translucency", Translucency); //0,25,50,75
	IsTiberium = artSection->readBoolValue("IsTiberium", IsTiberium);
	YSortAdjust = artSection->readIntValue("YSortAdjust", YSortAdjust);
	Elasticity = artSection->readFloatValue("Elasticity", Elasticity);
	MaxXYVel = artSection->readFloatValue("MaxXYVel", MaxXYVel);
	MinZVel = artSection->readFloatValue("MinZVel", MinZVel);
	IsMeteor = artSection->readBoolValue("IsMeteor", IsMeteor);
	IsVeins = artSection->readBoolValue("IsVeins", IsVeins);
	IsAnimatedTiberium = artSection->readBoolValue("IsAnimatedTiberium", IsAnimatedTiberium);
	YDrawOffset = artSection->readIntValue("YDrawOffset", YDrawOffset);
	ZAdjust = artSection->readIntValue("ZAdjust", ZAdjust);
	Tiled = artSection->readBoolValue("Tiled", Tiled);
	ShouldUseCellDrawer = artSection->readBoolValue("ShouldUseCellDrawer", ShouldUseCellDrawer);
	UseNormalLight = artSection->readBoolValue("UseNormalLigt", UseNormalLight);
}