#include "stdafx.h"
#include "EventCollection.hpp"
#include "ParamCollection.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Config.hpp"
#include "../../Log.hpp"
#include "../../GameDefinition.h"
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

	actions->readIntValue("RA2", rBaseCount);
	
	actions->readIntValue("YR", rExpCount);

	// Load only the first 59 entries if this is RA2
	if (Game::title == Game::Type::Base)
	{
		count = BaseCount;
	}
	// Load only the first 146 entries if Ares is not enabled
	else if (Game::title == Game::Type::Expansion && Config::hasAres == false)
	{
		count = ExpCount;
	}
	else
	{
		count = rExpCount;
	}

	for (int i = 0; i < count; ++i)
	{
		if (file->checkSectionExistance(Log::toString(i)))
			eventList.push_back(std::make_unique<EventType>(file->getSection(Log::toString(i)), paramColl));
		else
			break;
	}
}

EventType* EventCollection::get(int id)
{
	for (unsigned int i = 0; i < eventList.size(); ++i)
	{
		if (eventList[i]->identifier == id)
			return eventList[i].get();
	}

	return nullptr;
}