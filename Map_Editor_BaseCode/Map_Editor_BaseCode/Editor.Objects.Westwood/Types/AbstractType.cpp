#include "stdafx.h"
#include "AbstractType.hpp"


AbstractType::AbstractType(INISection* _rulesSection, INISection* _artSection)
:rulesSection(_rulesSection), artSection(_artSection)
{
	ID = rulesSection->getSectionName();
}

void AbstractType::loadRules()
{
	Name = rulesSection->readStringValue("Name", "MISSING Name");
	UIName = "TODO: UIName - " + rulesSection->readStringValue("UIName", "MISSING UIName");
}

void AbstractType::loadArt()
{

}