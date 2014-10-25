#include "stdafx.h"
#include "SActionCollection.hpp"
#include "ParamCollection.hpp"
#include "../../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../../Config.hpp"
#include "../../../Log.hpp"
#include "../../../GameDefinition.h"
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
	INIFile* file = INIManager::instance()->getRoot("ACTIONS_S");
	INISection* actions = file->getSection("ScriptActions");

	actions->readIntValue("RA2", rBaseCount);
	actions->readIntValue("YR", rExpCount);

	if (Game::title == Game::Type::Base)
	{
		count = BaseCount;
	}
	// Load only the first 146 entries if Ares is not enabled
	else if (Game::title == Game::Type::Expansion && Config::hasAres == false)
	{
		count = expCount;
	}
	else
	{
		count = rExpCount;
	}

	for (int i = 0; i < count; ++i)
	{
		if (file->sectionExists(Log::toString(i)))
			actionList.push_back(std::make_unique<SActionType>(file->getSection(Log::toString(i)), paramColl));
		else
			break;
	}
}

SActionType* SActionCollection::get(int id)
{
	for (unsigned int i = 0; i < actionList.size(); ++i)
	{
		if (actionList[i]->identifier == id)
			return actionList[i].get();
	}
	return nullptr;
}