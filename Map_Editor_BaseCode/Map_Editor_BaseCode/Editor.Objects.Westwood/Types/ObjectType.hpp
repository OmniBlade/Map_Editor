#pragma once

#include <string>
#include "AbstractType.hpp"
#include "../../Editor.FileSystem/INIFile/INISection.hpp"

class ObjectType : public AbstractType
{
public:
	ObjectType(INISection* _rulesSection, INISection* _artSection);

	void loadRules() override;
	void loadArt() override;

	std::string Image = "";
	std::string AlphaImage = "";
	bool Theater = false;
	bool NewTheater = false;
	bool Voxel = false;

protected:
	INISection* rulesSection = nullptr;
	INISection* artSection = nullptr;
};

