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

	rulesSection->readStringValue("Name", Name, Name);
	rulesSection->readStringValue("UIName", UIName, UIName);

	if (!UIName.empty())
	{
		if (Config::hasAres && UIName.substr(0, 6) == "NOSTR:")
		{
			std::string& UINameNOSTR = UIName.substr(6);
			WUIName.assign(UINameNOSTR.begin(), UINameNOSTR.end());
		}
		else
		{
			WUIName = CSFManager::getManager()->getValue(UIName);
		}
	}
	valid = true;
}

void AbstractType::loadArt(INIFile* art)
{
	//Nothing
}