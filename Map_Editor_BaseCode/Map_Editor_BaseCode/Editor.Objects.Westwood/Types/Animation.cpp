#include "stdafx.h"
#include "Animation.hpp"
#include "../../Log.hpp"
#include "WarheadType.hpp"
#include "ParticleType.hpp"
#include "OverlayType.hpp"

/* static */ WWList<Animation> Animation::Array;

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

	/*
		Could be considered hacky, but animations are a special case, they don't exist in rules but only in art
		Thus it would render them invalid though valid when only existing in art
		Mind you that this only applies here (in Animation)
	*/
	AbstractType::valid = true;

	artSection->readStringValue("Next", Next);
	artSection->readStringValue("Spawns", Spawns);
	artSection->readStringValue("TiberiumSpawnType", TiberiumSpawnType);
	artSection->readStringValue("BounceAnim", BounceAnim);
	artSection->readStringValue("ExpireAnim", ExpireAnim);
	artSection->readStringValue("TrailerAnim", TrailerAnim);
	artSection->readStringValue("Warhead", Warhead);
	artSection->readStringValue("SpawnsParticle", SpawnsParticle);

	Animation::Array.findOrAllocate(Next);
	Animation::Array.findOrAllocate(Spawns);
	OverlayType::Array.findOrAllocate(TiberiumSpawnType);
	Animation::Array.findOrAllocate(BounceAnim);
	Animation::Array.findOrAllocate(ExpireAnim);
	Animation::Array.findOrAllocate(TrailerAnim);
	WarheadType::Array.findOrAllocate(Warhead);
	ParticleType::Array.findOrAllocate(SpawnsParticle);

	artSection->readBoolValue("Shadow", Shadow);
	artSection->readBoolValue("AltPalette", AltPalette);
	artSection->readBoolValue("Flat", Flat);
	artSection->readBoolValue("Normalized", Normalized);
	artSection->readBoolValue("Translucent", Translucent);
	artSection->readBoolValue("Scorch", Scorch);
	artSection->readBoolValue("Crater", Crater);
	artSection->readBoolValue("ForceBigCraters", ForceBigCraters);
	artSection->readIntValue("Start", Start);
	artSection->readIntValue("End", End);
	artSection->readIntValue("LoopStart", LoopStart);
	artSection->readIntValue("LoopEnd", LoopEnd);
	artSection->readIntValue("LoopCount", LoopCount);
	artSection->readStringValue("Next", Next);
	artSection->readIntValue("Translucency", Translucency); //0,25,50,75
	artSection->readBoolValue("IsTiberium", IsTiberium);
	artSection->readIntValue("YSortAdjust", YSortAdjust);
	artSection->readFloatValue("Elasticity", Elasticity);
	artSection->readFloatValue("MaxXYVel", MaxXYVel);
	artSection->readFloatValue("MinZVel", MinZVel);
	artSection->readBoolValue("IsMeteor", IsMeteor);
	artSection->readBoolValue("IsVeins", IsVeins);
	artSection->readBoolValue("IsAnimatedTiberium", IsAnimatedTiberium);
	artSection->readIntValue("YDrawOffset", YDrawOffset);
	artSection->readIntValue("ZAdjust", ZAdjust);
	artSection->readBoolValue("Tiled", Tiled);
	artSection->readBoolValue("ShouldUseCellDrawer", ShouldUseCellDrawer);
	artSection->readBoolValue("UseNormalLigt", UseNormalLight);
}