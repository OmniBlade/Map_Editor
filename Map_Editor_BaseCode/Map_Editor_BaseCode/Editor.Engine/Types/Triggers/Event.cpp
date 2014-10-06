#include "stdafx.h"
#include "Event.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"

/* static */ MapObjectList<Event> Event::Array;

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
			Log::line("Unable to parse Event with ID '" + ID + "'.", Log::DEBUG);
		}
	}

	if (eventList.size() != count)
	{
		Log::line("Event with ID '" + ID + "' does not have the amount of SubEvents it is supposed to have.", Log::DEBUG);
	}
}

void Event::writeToINI(INIFile& file)
{
	for (auto& it : Array.objectTypeList)
	{
		file.SetValue("Events", it->ID, it->asString());
	}
}

std::string Event::asString()
{
	std::string params;

	for (auto& it : eventList)
	{
		params.append(it->asString());
	}

	char buffer[512];
	sprintf_s(buffer, 512, "%d%s",
		this->count,
		params.c_str()
		);

	return buffer;

}