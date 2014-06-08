#include "stdafx.h"
#include "ActionCollection.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Config.hpp"
#include "../../Log.hpp"
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

void ActionCollection::parse()
{
	INIFile* file = INIManager::getManager()->getRoot("ACTIONS");
	INISection* actions = file->getSection("Actions");

	actions->readIntValue("Count", count);
	
	// Load only the first 146 entries if Ares is not enabled
	if (count < 0 || (count > YRCount && Config::hasAres == false))
	{
		count = YRCount;
	}

	for (int i = 0; i < count; ++i)
	{
		if (file->checkSectionExistance(Log::toString(i)))
			actionList.push_back(std::make_unique<ActionTemplate>(file->getSection(Log::toString(i))));
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