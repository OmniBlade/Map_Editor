#include "stdafx.h"
#include "Tiberium.hpp"

/* static */ List<Tiberium> Tiberium::Array;

Tiberium::Tiberium(const std::string& id)
:ObjectType(id)
{
}

void Tiberium::loadRules(INIFile* rules)
{
	INISection* rulesSection = rules->getSection(ID);
	if (!rulesSection) return;

	ObjectType::loadRules(rules);

	rulesSection->readIntValue("Value", Value);
	rulesSection->readIntValue("Power", Power);
	rulesSection->readStringValue("Color", Color);
	rulesSection->readIntValue("Image", Image);
}

void Tiberium::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	ObjectType::loadArt(art);
}