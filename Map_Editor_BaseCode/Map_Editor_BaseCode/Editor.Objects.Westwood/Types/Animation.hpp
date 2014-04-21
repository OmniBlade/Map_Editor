#pragma once

#include "../../Editor.FileSystem/INIFile/INISection.hpp"
#include "../Managers/List.hpp"
#include "ObjectType.hpp"

class Animation : public ObjectType
{
public:
	static List<Animation> Array;
	Animation(const std::string& id);

	void loadRules(INIFile* rules) override;
	void loadArt(INIFile* art) override;

	bool Shadow = false;
	bool AltPalette = false;
	bool Flat = false;
	bool Normalized = false;
	bool Translucent = false;
	bool Scorch = false;
	bool Crater = false;
	bool ForceBigCraters = false;
	int Start = 0;
	int End = 0;
	int LoopStart = 0;
	int LoopEnd = 0;
	int LoopCount = 0;
	std::string Next = "";
	int Translucency; //0,25,50,75
	bool IsTiberium = false;
	int YSortAdjust = 0;
	float Elasticity = 0.8f;
	float MaxXYVel = 2.71875;
	float MinZVel = 2.1875;
	bool IsMeteor = false;
	bool IsVeins = false;
	bool IsAnimatedTiberium = false;
	//bool ShouldFogRemove;
	int YDrawOffset = 0;
	int ZAdjust = 0;
	bool Tiled = false;
	bool ShouldUseCellDrawer = false;
	bool UseNormalLight = false;
};

