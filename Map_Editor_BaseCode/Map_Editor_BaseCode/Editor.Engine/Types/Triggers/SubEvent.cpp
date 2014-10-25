#include "stdafx.h"
#include "SubEvent.hpp"
#include "../../../Editor.FileSystem/MapFile/Triggers/EventCollection.hpp"
#include "../../../Editor.FileSystem/MapFile/Triggers/EventType.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Log.hpp"

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

std::string SubEvent::asString()
{
	char buffer[512];

	if (parseType == 2)
	{
		char buffer[512];
		sprintf_s(buffer, 512, ",%d,%d,%d,%s",
			this->eventType,
			this->parseType,
			this->params[0].Index,
			paramAsString(1).c_str()
			);

		return buffer;
	}
	else
	{
		sprintf_s(buffer, 512, ",%d,%d,%s",
			this->eventType,
			this->parseType,
			paramAsString(0).c_str()
			);

		return buffer;
	}
}

std::string SubEvent::paramAsString(int paramNumber)
{
	std::string ret;

	if (params[paramNumber].ID.empty())
	{
		ret = Log::toString(params[paramNumber].Index);
	}
	else
	{
		ret = params[paramNumber].ID;
	}

	return ret;
}