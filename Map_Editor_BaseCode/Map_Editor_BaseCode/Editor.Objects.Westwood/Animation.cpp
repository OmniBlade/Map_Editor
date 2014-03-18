#include "stdafx.h"
#include "Animation.hpp"


Animation::Animation(INISection* _rulesSection, INISection* _artSection)
:ObjectType(_rulesSection, _artSection), artSection(_artSection), rulesSection(_rulesSection)
{
}

void Animation::loadRules()
{

}

void Animation::loadArt()
{
	Shadow = artSection->readBoolValue("Shadow", false);
	AltPalette = artSection->readBoolValue("AltPalette", false);
	Flat = artSection->readBoolValue("Flat", false);
	Normalized = artSection->readBoolValue("Normalized", false);
	Translucent = artSection->readBoolValue("Translucent", false);
	Scorch = artSection->readBoolValue("Scorch", false);
	Crater = artSection->readBoolValue("Crater", false);
	ForceBigCraters = artSection->readBoolValue("ForceBigCraters", false);
	Start = artSection->readIntValue("Start", 0);
	End = artSection->readIntValue("End", 0);
	LoopStart = artSection->readIntValue("LoopStart", 0);
	LoopEnd = artSection->readIntValue("LoopEnd", 0);
	LoopCount = artSection->readIntValue("LoopCount", 0);
	Next = artSection->readStringValue("Next", "");
	Translucency = artSection->readIntValue("Translucency", 0);; //0,25,50,75
	IsTiberium = artSection->readBoolValue("IsTiberium", false);
	YSortAdjust = artSection->readIntValue("YSortAdjust", 0);
	Elasticity = artSection->readFloatValue("Elasticity", 0.8);
	MaxXYVel = artSection->readBoolValue("MaxXYVel", 2.71875);
	MinZVel = artSection->readFloatValue("MinZVel", 2.1875);
	IsMeteor = artSection->readBoolValue("IsMeteor", false);
	IsVeins = artSection->readBoolValue("IsVeins", false);
	IsAnimatedTiberium = artSection->readBoolValue("IsAnimatedTiberium", false);
	YDrawOffset = artSection->readIntValue("YDrawOffset", 0);
	ZAdjust = artSection->readIntValue("ZAdjust", 0);
	Tiled = artSection->readBoolValue("Tiled", false);
	ShouldUseCellDrawer = artSection->readBoolValue("ShouldUseCellDrawer", false);
	UseNormalLight = artSection->readBoolValue("UseNormalLigt", false);
}