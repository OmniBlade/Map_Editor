#include "stdafx.h"
#include "EventType.hpp"
#include "ParamCollection.hpp"
#include "ParamType.hpp"
#include "../../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Log.hpp"
#include <sstream>

EventType::EventType(INISection* section, ParamCollection* params)
{
	parse(section, params);
}

void EventType::parse(INISection* section, ParamCollection* params)
{
	section->readIntValue("Identifier", identifier, atoi(section->getSectionName().c_str()));
	section->readStringValue("Name", name);
	section->readStringValue("Description", description);
	section->readStringValue("TagCode", tagCode);
	section->readStringValue("ParamString", paramString, "0,0");
	section->readBoolValue("RequiresAres", requiresAres, false);
	section->readBoolValue("Works", works, true);

	LineSplitter split(paramString);
	for (unsigned int i = 0; i < split.size(); ++i)
	{
		auto it = params->get(split.peekFromIndex_int(i));
		paramList.push_back(it);
		
		if (it && it->listIndex > 0)
		{
			nonZeroParamList.push_back(it);
		}
	}

	if (split.pop(P1) && split.pop(P2))
	{
		//Load the third parameter for special YR Events
		if (P1 == -2)
		{
			//Game expects 2 parameters, only 1 is found
			if (!split.pop(P3))
			{
				//Add another ParamType for the Event
				if (P3 > 0)
					paramList.push_back(params->get(P2));

				Log::line("Event with ID '" + section->getSectionName() + "' has too few parameters in its ParamString.", Log::DEBUG);
			}
		}
	}
	else
	{
		Log::line("Unable to parse Event with ID '" + section->getSectionName() + "', invalid ParamString.", Log::DEBUG);
	}
}

std::string EventType::getNameWithParams()
{
	unsigned int replacerNum = 1;
	std::string ret = this->name;

	for (unsigned int i = 0; i < nonZeroParamList.size(); ++i)
	{
		std::string replacer = INameHelper::getReplacer(replacerNum);

		std::size_t pos = ret.find(replacer);
		if (pos != std::string::npos)
		{
			std::string rep1 = ret.substr(0, pos);
			std::string rep2 = ret.substr(pos + 4, ret.size());

			ret = rep1 + nonZeroParamList[i]->name + rep2;
		}
		replacerNum++;
	}

	return ret;
}