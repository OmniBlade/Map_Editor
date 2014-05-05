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

	rulesSection->readBoolValue("Wall", Wall);
	rulesSection->readBoolValue("Tiberium", Tiberium);
	rulesSection->readBoolValue("Crate", Crate);
	rulesSection->readBoolValue("CrateTrigger", CrateTrigger);
	rulesSection->readBoolValue("Overrides", Overrides);
	rulesSection->readStringValue("CellAnim", CellAnim);
	rulesSection->readIntValue("DamageLevels", DamageLevels);
	rulesSection->readStringValue("RadarColor", RadarColor); //TODO: Implement RGB color
	rulesSection->readBoolValue("NoUseLandTileType", NoUseLandTileType);
	rulesSection->readBoolValue("IsVeinholeMonster", IsVeinholeMonster);
	rulesSection->readBoolValue("IsVeins", IsVeins);
	rulesSection->readBoolValue("DrawFlat", DrawFlat);
	rulesSection->readBoolValue("IsRubble", IsRubble);
}

void OverlayType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	ObjectType::loadArt(art);
}