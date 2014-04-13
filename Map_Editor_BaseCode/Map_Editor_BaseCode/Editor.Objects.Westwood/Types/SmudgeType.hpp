#pragma once

#include "ObjectType.hpp"

class SmudgeType : public ObjectType
{
public:
	SmudgeType(INISection* _rulesSection, INISection* _artSection);

	void loadRules() override;
	void loadArt() override;

	bool Crater;
	bool Smudge;
	int Width;
	int Height;

protected: 
	INISection* rulesSection = nullptr;
	INISection* artSection = nullptr;
};

