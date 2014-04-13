#pragma once

#include <string>
#include "../../Editor.FileSystem/INIFile/INISection.hpp"

class AbstractType
{
public:
	AbstractType(INISection* _rulesSection, INISection* _artSection);

	virtual void loadRules();
	virtual void loadArt();

	std::string ID;
	std::string Name;
	std::string UIName;

protected:
	INISection* rulesSection = nullptr;
	INISection* artSection = nullptr;
};

