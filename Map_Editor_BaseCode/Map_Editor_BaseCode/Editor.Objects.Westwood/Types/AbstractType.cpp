#include "stdafx.h"
#include "AbstractType.hpp"
#include "../../Editor.FileSystem/INIFile/INISection.hpp"
#include "../../Editor.FileSystem/CSFFile/CSFFile.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/CSFManager.hpp"
#include "../../Config.hpp"

AbstractType::AbstractType(const std::string& id)
:ID(id), valid(false)
{
}

void AbstractType::loadRules(INIFile* rules)
{
	INISection* rulesSection = rules->getSection(ID);

	rulesSection->readStringValue("Name", Name, Name.c_str());
	rulesSection->readStringValue("UIName", UIName, UIName.c_str());

	if (!UIName.empty())
	{
		WUIName = CSFManager::getManager()->getValue(UIName);
	}
	valid = true;
}

void AbstractType::loadArt(INIFile* art)
{
	//Nothing
}