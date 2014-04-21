#pragma once

#include "ObjectType.hpp"

class Tiberium : public ObjectType
{
public:
	Tiberium(const std::string& id);

	void loadRules(INIFile* rules) override;
	void loadArt(INIFile* art) override;

	int Value = 0;
	int Power = 0;
	std::string Color = "";
	int Image = 0;
};

