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

		switch (ret->parseType)
		{
		case 2: //TechnoType, number first, then ID
			ret->params.resize(2);
			ret->params.reserve(2);
			parts.pop(ret->params[0].Index);
			parts.pop(ret->params[1].ID);
			break;
		case 1: //TeamType, ID only
			ret->params.resize(1);
			ret->params.reserve(1);
			parts.pop(ret->params[0].ID);
			break;
		default:
		case 0: //Others, numbers only
			ret->params.resize(1);
			ret->params.reserve(1);
			parts.pop(ret->params[0].Index);
			break;
		}
		return ret;
	}

	return nullptr;
}

void SubEvent::assignEventType()
{
	pEventType = EventCollection::getInstance()->get(eventType);
	if (!pEventType)
		Log::line("Unable to get EventType for SubEvent with ID " + Log::toString(eventType) + ".", Log::DEBUG);
}