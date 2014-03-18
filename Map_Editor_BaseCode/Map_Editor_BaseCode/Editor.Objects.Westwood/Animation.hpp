#pragma once

#include "../Editor.FileSystem/INIFile/INISection.hpp"
#include "ObjectType.hpp"

class Animation : public ObjectType
{
public:
	Animation(INISection* _rulesSection, INISection* _artSection);

	void loadRules() override;
	void loadArt() override;

	bool Shadow;
	bool AltPalette;
	bool Flat;
	bool Normalized;
	bool Translucent;
	bool Scorch;
	bool Crater;
	bool ForceBigCraters;
	int Start;
	int End;
	int LoopStart;
	int LoopEnd;
	int LoopCount;
	std::string Next;
	int Translucency; //0,25,50,75
	bool IsTiberium;
	int YSortAdjust;
	float Elasticity;
	float MaxXYVel;
	float MinZVel;
	bool IsMeteor;
	bool IsVeins;
	bool IsAnimatedTiberium;
	//bool ShouldFogRemove;
	int YDrawOffset;
	int ZAdjust;
	bool Tiled;
	bool ShouldUseCellDrawer;
	bool UseNormalLight;

protected:
	INISection* rulesSection = nullptr;
	INISection* artSection = nullptr;
};

