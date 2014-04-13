#include "stdafx.h"
#include "SmudgeType.hpp"


SmudgeType::SmudgeType(INISection* _rulesSection, INISection* _artSection)
:ObjectType(_rulesSection, _artSection), artSection(_artSection), rulesSection(_rulesSection)
{

}

void  SmudgeType::loadRules()
{
	Crater = rulesSection->readBoolValue("Crater", false);
	Smudge = rulesSection->readBoolValue("Smudge", false);
	Width = rulesSection->readIntValue("Width", 1);
	Height = rulesSection->readIntValue("Height", 1);
}

void SmudgeType::loadArt()
{

}