#pragma once

#include <string>
#include "../../Editor.FileSystem/INIFile/INISection.hpp"
#include "TechnoType.hpp"

class InfantryType : public TechnoType
{
public:
	InfantryType(INISection* _rulesSection, INISection* _artSection);

	void loadRules() override;
	void loadArt() override;

	bool Cyborg;
	bool NotHuman;
	bool Occupier;
	bool Civilian;

protected:
	INISection* rulesSection;
	INISection* artSection;
};

