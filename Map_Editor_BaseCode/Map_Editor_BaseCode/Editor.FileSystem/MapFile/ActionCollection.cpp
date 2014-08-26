#include "stdafx.h"
#include "ActionCollection.hpp"
#include "ParamCollection.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Config.hpp"
#include "../../Log.hpp"
#include "../../GameDefinition.h"
#include <string>

/* static */ ActionCollection* ActionCollection::instance;
/* static */ ActionCollection* ActionCollection::getInstance()
{
	if (instance)
		return instance;
	else
		instance = new ActionCollection();

	return instance;
}

ActionCollection::ActionCollection()
{

}

void ActionCollection::parse(ParamCollection* paramColl)
{
	paramColl = paramColl;
	INIFile* file = INIManager::getManager()->getRoot("ACTIONS");
	INISection* actions = file->getSection("Actions");

	actions->readIntValue("RA2", rBaseCount);
	actions->readIntValue("YR", rExpCount);
	
	if (Game::title == Game::Type::Base)
	{
		count = BaseCount;
	}
	// Load only the first 146 entries if Ares is not enabled
	else if (rExpCount < 0 || (rExpCount > expCount && Config::hasAres == false))
	{
		count = expCount;
	}
	else
	{
		count = rExpCount;
	}

	for (int i = 0; i < count; ++i)
	{
		if (file->checkSectionExistance(Log::toString(i)))
			actionList.push_back(std::make_unique<ActionTemplate>(file->getSection(Log::toString(i)), paramColl));
		else
			break;
	}
}

ActionTemplate* ActionCollection::get(int id)
{
	for (unsigned int i = 0; i < actionList.size(); ++i)
	{
		if (actionList[i]->identifier == id)
			return actionList[i].get();
	}
	return nullptr;
}