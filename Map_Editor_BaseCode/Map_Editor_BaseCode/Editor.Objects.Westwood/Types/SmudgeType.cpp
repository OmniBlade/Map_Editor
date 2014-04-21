#include "stdafx.h"
#include "SmudgeType.hpp"
#include "../../Log.hpp"

/* static */ List<SmudgeType> SmudgeType::Array;

SmudgeType::SmudgeType(const std::string& id)
:ObjectType(id)
{
}

void  SmudgeType::loadRules(INIFile* rules)
{
	INISection* rulesSection = rules->getSection(ID);
	if (!rulesSection) return;

	ObjectType::loadRules(rules);

	Crater = rulesSection->readBoolValue("Crater", Crater);
	Smudge = rulesSection->readBoolValue("Smudge", Smudge);
	Width = rulesSection->readIntValue("Width", Width);
	Height = rulesSection->readIntValue("Height", Height);
}

void SmudgeType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	ObjectType::loadArt(art);
}