#include "stdafx.h"
#include "SActionCollection.hpp"
#include "ParamCollection.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Config.hpp"
#include "../../Log.hpp"
#include <string>

/* static */ SActionCollection* SActionCollection::instance;
/* static */ SActionCollection* SActionCollection::getInstance()
{
	if (instance)
		return instance;
	else
		instance = new SActionCollection();

	return instance;
}

SActionCollection::SActionCollection()
{

}

void SActionCollection::parse(ParamCollection* paramColl)
{
	paramColl = paramColl;
	INIFile* file = INIManager::getManager()->getRoot("SACTIONS");
	INISection* actions = file->getSection("ScriptActions");

	actions->readIntValue("Count", count);

	// Load only the first 146 entries if Ares is not enabled
	if (count < 0 || (count > YRCount && Config::hasAres == false))
	{
		count = YRCount;
	}

	for (int i = 0; i < count; ++i)
	{
		if (file->checkSectionExistance(Log::toString(i)))
			actionList.push_back(std::make_unique<SActionTemplate>(file->getSection(Log::toString(i)), paramColl));
		else
			break;
	}
}

SActionTemplate* SActionCollection::get(int id)
{
	for (unsigned int i = 0; i < actionList.size(); ++i)
	{
		if (actionList[i]->identifier == id)
			return actionList[i].get();
	}
	return nullptr;
}