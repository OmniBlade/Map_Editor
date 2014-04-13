#pragma once

#include "ObjectType.hpp"

class Tiberium : public ObjectType
{
public:
	Tiberium(INISection* _rulesSection, INISection* _artSection);

	void loadRules() override;
	void loadArt() override;

	int Value;
	int Power;
	std::string Color;
	int Image;

protected:
	INISection* rulesSection = nullptr;
	INISection* artSection = nullptr;
};

