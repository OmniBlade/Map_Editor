#include "stdafx.h"
#include "OverlayType.hpp"


OverlayType::OverlayType(INISection* _rulesSection, INISection* _artSection)
:ObjectType(_rulesSection, _artSection), artSection(_artSection), rulesSection(_rulesSection)
{
	loadRules();
}


void OverlayType::loadRules()
{

	Wall = rulesSection->readBoolValue("Wall", false);
	Tiberium = rulesSection->readBoolValue("Tiberium", false);
	Crate = rulesSection->readBoolValue("Crate", false);
	CrateTrigger = rulesSection->readBoolValue("CrateTrigger", false);
	Overrides = rulesSection->readBoolValue("Overrides", false);
	CellAnim = rulesSection->readStringValue("CellAnim", "");
	DamageLevels = rulesSection->readIntValue("DamageLevels", 1);
	RadarColor = rulesSection->readStringValue("RadarColor", ""); //TODO: Implement RGB color
	NoUseLandTileType = rulesSection->readBoolValue("NoUseLandTileType", true);
	IsVeinholeMonster = rulesSection->readBoolValue("IsVeinholeMonster", false);
	IsVeins = rulesSection->readBoolValue("IsVeins", false);
	DrawFlat = rulesSection->readBoolValue("DrawFlat", true);
	IsRubble = rulesSection->readBoolValue("IsRubble", false);
}

void OverlayType::loadArt()
{

}