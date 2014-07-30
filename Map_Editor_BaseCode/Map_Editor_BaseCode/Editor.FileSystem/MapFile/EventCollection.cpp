#include "stdafx.h"
#include "EventCollection.hpp"
#include "ParamCollection.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Config.hpp"
#include "../../Log.hpp"
#include <string>

/* static */ EventCollection* EventCollection::instance;
/* static */ EventCollection* EventCollection::getInstance()
{
	if (instance)
		return instance;
	else
		instance = new EventCollection();

	return instance;
}

EventCollection::EventCollection()
{

}

void EventCollection::parse(ParamCollection* paramColl)
{
	paramColl = paramColl;
	INIFile* file = INIManager::getManager()->getRoot("EVENTS");
	INISection* actions = file->getSection("Events");

	actions->readIntValue("Count", count);

	// Load only the first 146 entries if Ares is not enabled
	if (count < 0 || (count > YRCount && Config::hasAres == false))
	{
		count = YRCount;
	}

	for (int i = 0; i < count; ++i)
	{
		if (file->checkSectionExistance(Log::toString(i)))
			eventList.push_back(std::make_unique<EventTemplate>(file->getSection(Log::toString(i)), paramColl));
		else
			break;
	}
}

EventTemplate* EventCollection::get(int id)
{
	for (unsigned int i = 0; i < eventList.size(); ++i)
	{
		if (eventList[i]->identifier == id)
			return eventList[i].get();
	}

	return nullptr;
}