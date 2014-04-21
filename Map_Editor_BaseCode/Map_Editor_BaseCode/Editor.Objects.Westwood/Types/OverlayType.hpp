#pragma once

#include "ObjectType.hpp"
#include "../Managers/List.hpp"
#include <string>

class OverlayType : public ObjectType
{
public:
	static List<OverlayType> Array;
	OverlayType(const std::string& id);

	void loadRules(INIFile* rules) override;
	void loadArt(INIFile* art) override;

	bool Wall = false;
	bool Tiberium = false;
	bool Crate = false;
	bool CrateTrigger = false;
	bool Overrides = false;
	std::string CellAnim = "";
	int DamageLevels = 1;
	std::string RadarColor = "";
	bool NoUseLandTileType = true;
	bool IsVeinholeMonster = false;
	bool IsVeins = false;
	bool DrawFlat = true;
	bool IsRubble = false;
};

