#include "stdafx.h"
#include "AbstractType.hpp"
#include "../../Editor.FileSystem/INIFile/INISection.hpp"

AbstractType::AbstractType(const std::string& id)
:ID(id), valid(false)
{
}

void AbstractType::loadRules(INIFile* rules)
{
	INISection* rulesSection = rules->getSection(ID);

	Name = rulesSection->readStringValue("Name", Name);
	UIName = "TODO: UIName - " + rulesSection->readStringValue("UIName", UIName);
	valid = true;
}

void AbstractType::loadArt(INIFile* art)
{
	//Nothing
}