#include "stdafx.h"
#include "EventTemplate.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "ParamCollection.hpp"
#include "ParamType.hpp"
#include "../../Log.hpp"

EventTemplate::EventTemplate(INISection* section, ParamCollection* params)
{
	parse(section, params);
}

void EventTemplate::parse(INISection* section, ParamCollection* params)
{
	section->readIntValue("Identifier", identifier, atoi(section->getSectionName().c_str()));
	section->readStringValue("Name", name);
	section->readStringValue("Description", description);
	section->readStringValue("TagCode", tagCode);
	section->readStringValue("ParamString", paramString, "0,0");
	section->readBoolValue("RequiresAres", requiresAres, false);
	section->readBoolValue("Works", works, true);

	if (paramString == "0,0")
		return;

	LineSplitter split(paramString);
	if (split.pop(P1) && split.pop(P2))
	{
		//Add a ParamType for the Event
		if (P2 > 0)
			paramList.push_back(params->get(P2));

		//Load the third parameter for special YR Events
		if (P1 == -2)
		{
			//Game expects 2 parameters, only 1 is found
			if (!split.pop(P3))
			{
				//Add another ParamType for the Event
				if (P3 > 0)
					paramList.push_back(params->get(P2));

				Log::note("Event with ID '" + section->getSectionName() + "' has too few parameters in its ParamString.", Log::DEBUG);
			}
		}
	}
	else
	{
		Log::note("Unable to parse Event with ID '" + section->getSectionName() + "', invalid ParamString.", Log::DEBUG);
	}
}