#pragma once

#include <string>
#include "AbstractType.hpp"

class ObjectType : public AbstractType
{
public:
	ObjectType(const std::string& id);

	void loadRules(INIFile* rules) override;
	void loadArt(INIFile* art) override;

	std::string Image = "";
	std::string AlphaImage = "";
	bool Theater = false;
	bool NewTheater = false;
	bool Voxel = false;
};

