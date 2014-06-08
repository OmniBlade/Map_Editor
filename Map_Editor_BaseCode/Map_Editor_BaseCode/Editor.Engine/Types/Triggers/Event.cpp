#include "stdafx.h"
#include "Event.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"

/* static */ ObjectList<Event> Event::Array;

Event::Event()
{
}

void Event::parse(const std::string& id, const std::string& list)
{
	ID = std::move(id);
	List = std::move(list);
}

void Event::parseEvents()
{
	LineSplitter parts(List);

	count = std::move(parts.pop_int());

	while (!parts.empty())
	{
		if (auto sub = SubEvent::parse(parts))
		{
			eventList.push_back(sub);
		}
		else
		{
			Log::note("Unable to parse Event with ID '" + ID + "'.", Log::DEBUG);
		}
	}

	if (eventList.size() != count)
	{
		Log::note("Event with ID '" + ID + "' does not have the amount of SubEvents it is supposed to have.", Log::DEBUG);
	}
}