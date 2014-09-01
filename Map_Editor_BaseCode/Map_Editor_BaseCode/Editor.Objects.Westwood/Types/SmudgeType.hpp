#pragma once

#include "../Managers/WWList.hpp"
#include "ObjectType.hpp"

class SmudgeType : public ObjectType
{
public:
	static WWList<SmudgeType> Array;

	SmudgeType(const std::string& id);

	void loadRules(INIFile* rules) override;
	void loadArt(INIFile* art) override;

	bool Crater = false;
	bool Smudge = false;
	int Width = 1;
	int Height = 1;
};

