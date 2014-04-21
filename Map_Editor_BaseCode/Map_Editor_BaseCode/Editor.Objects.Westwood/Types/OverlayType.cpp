#include "stdafx.h"
#include "OverlayType.hpp"
#include "../../Log.hpp"

/* static */ List<OverlayType> OverlayType::Array;

OverlayType::OverlayType(const std::string& id)
:ObjectType(id)
{
}


void OverlayType::loadRules(INIFile* rules)
{
	INISection* rulesSection = rules->getSection(ID);
	if (!rulesSection) return;

	ObjectType::loadRules(rules);

	Wall = rulesSection->readBoolValue("Wall", Wall);
	Tiberium = rulesSection->readBoolValue("Tiberium", Tiberium);
	Crate = rulesSection->readBoolValue("Crate", Crate);
	CrateTrigger = rulesSection->readBoolValue("CrateTrigger", CrateTrigger);
	Overrides = rulesSection->readBoolValue("Overrides", Overrides);
	CellAnim = rulesSection->readStringValue("CellAnim", CellAnim);
	DamageLevels = rulesSection->readIntValue("DamageLevels", DamageLevels);
	RadarColor = rulesSection->readStringValue("RadarColor", RadarColor); //TODO: Implement RGB color
	NoUseLandTileType = rulesSection->readBoolValue("NoUseLandTileType", NoUseLandTileType);
	IsVeinholeMonster = rulesSection->readBoolValue("IsVeinholeMonster", IsVeinholeMonster);
	IsVeins = rulesSection->readBoolValue("IsVeins", IsVeins);
	DrawFlat = rulesSection->readBoolValue("DrawFlat", DrawFlat);
	IsRubble = rulesSection->readBoolValue("IsRubble", IsRubble);
}

void OverlayType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	ObjectType::loadArt(art);
}