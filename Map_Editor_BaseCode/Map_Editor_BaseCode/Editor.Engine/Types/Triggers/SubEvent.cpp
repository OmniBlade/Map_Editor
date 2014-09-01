#include "stdafx.h"
#include "SubEvent.hpp"
#include "../../../Editor.FileSystem/MapFile/EventCollection.hpp"
#include "../../../Editor.FileSystem/MapFile/EventType.hpp"
#include "../../../Log.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"

SubEvent::SubEvent()
: eventType(-1), parseType(-1)
{
	
}

/* static */ std::shared_ptr<SubEvent> SubEvent::parse(LineSplitter& parts)
{
	auto ret = std::make_shared<SubEvent>();

	if (parts.pop(ret->eventType) && parts.pop(ret->parseType))
	{
		ret->assignEventType();
		if (parts.pop(ret->param1S))
		{
			// only type 2 reads a third param
			if (ret->parseType != 2 || parts.pop(ret->param2))
			{
				return ret;
			}
		}
	}
	return nullptr;
}

void SubEvent::assignEventType()
{
	pEventType = EventCollection::getInstance()->get(eventType);
	if (!pEventType)
		Log::line("Unable to get EventType for SubEvent with ID " + Log::toString(eventType) + ".", Log::DEBUG);
}