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

	rulesSection->readBoolValue("Crater", Crater);
	rulesSection->readBoolValue("Smudge", Smudge);
	rulesSection->readIntValue("Width", Width);
	rulesSection->readIntValue("Height", Height);
}

void SmudgeType::loadArt(INIFile* art)
{
	INISection* artSection = art->getSection(ID);
	if (!artSection) return;

	ObjectType::loadArt(art);
}