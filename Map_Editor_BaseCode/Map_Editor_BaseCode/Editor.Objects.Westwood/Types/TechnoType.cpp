#include "stdafx.h"
#include "TechnoType.hpp"
#include "../../Editor.FileSystem/INIFile/LineSplitter.hpp"

TechnoType::TechnoType(INISection* _rulesSection, INISection* _artSection)
:ObjectType(_rulesSection, _artSection), artSection(_artSection), rulesSection(_rulesSection)
{
}

void TechnoType::loadRules()
{
	IsTrain = rulesSection->readBoolValue("IsTrain", false);
	Passengers = rulesSection->readIntValue("Passengers", 0);
	Size = rulesSection->readFloatValue("Size", 1.0);
	SizeLimit = rulesSection->readFloatValue("SizeLimit", 0.0);

	Turret = rulesSection->readBoolValue("Turret", false);
	TechLevel = rulesSection->readIntValue("TechLevel", 255);
	AIBasePlanningSide = rulesSection->readIntValue("AIBasePlanningSide", -1);

	NoShadow = rulesSection->readBoolValue("NoShadow", false);
	ZFudgeCliff = rulesSection->readIntValue("ZFudgeCliff", 10);
	ZFudgeColumn = rulesSection->readIntValue("ZFudgeColumn", 5);
	ZFudgeTunnel = rulesSection->readIntValue("ZFudgeTunnel", 10);
	ZFudgeBridge = rulesSection->readIntValue("ZFudgeBridge", 0);
}

void TechnoType::loadArt()
{
	Remapable = artSection->readBoolValue("Remapable", false);
	Palette = artSection->readStringValue("Palette", "");

	LineSplitter split(artSection->readStringValue("TurretOffset", "0,0,0"));
	TurretOffset.x = split.pop_int();
	TurretOffset.y = split.pop_int();
	TurretOffset.z = split.pop_int();
}