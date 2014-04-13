#pragma once

#include "ObjectType.hpp"
#include "../../Editor.FileSystem/INIFile/INISection.hpp"
#include <string>

class OverlayType : public ObjectType
{
public:
	OverlayType(INISection* _rulesSection, INISection* _artSection);

	void loadRules() override;
	void loadArt() override;

	bool Wall;
	bool Tiberium;
	bool Crate;
	bool CrateTrigger;
	bool Overrides;
	std::string CellAnim;
	int DamageLevels;
	std::string RadarColor;
	bool NoUseLandTileType;
	bool IsVeinholeMonster;
	bool IsVeins;
	bool DrawFlat;
	bool IsRubble;

protected:
	INISection* rulesSection;
	INISection* artSection;
};

