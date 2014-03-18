#include "stdafx.h"
#include "Tiberium.hpp"


Tiberium::Tiberium(INISection* _rulesSection, INISection* _artSection)
:ObjectType(_rulesSection, _artSection), artSection(_artSection), rulesSection(_rulesSection)
{
}

void Tiberium::loadRules()
{
	Value = rulesSection->readIntValue("Value", 0);
	Power = rulesSection->readIntValue("Power", 0);
	Color = rulesSection->readStringValue("Color", "");
	Image = rulesSection->readIntValue("Image", 0);
}

void Tiberium::loadArt()
{

}