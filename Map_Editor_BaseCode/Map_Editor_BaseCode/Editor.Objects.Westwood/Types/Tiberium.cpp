#include "stdafx.h"
#include "Tiberium.hpp"


Tiberium::Tiberium(const std::string& id)
:ObjectType(id)
{
}

void Tiberium::loadRules(INIFile* rules)
{
	INISection* rulesSection = rules->getSection(ID);
	if (!rulesSection) return;

	ObjectType::loadRules(rules);

	Value = rulesSection->readIntValue("Value", Value);
	Power = rulesSection->readIntValue("Power", Power);
	Color = rulesSection->readStringValue("Color", Color);
	Image = rulesSection->readIntValue("Image", Image);
}

void Tiberium::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	ObjectType::loadArt(art);
}