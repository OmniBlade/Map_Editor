#include "stdafx.h"
#include "SActionType.hpp"
#include "ParamCollection.hpp"
#include "ParamType.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../Log.hpp"

SActionType::SActionType(INISection* section, ParamCollection* params)
{
	parse(section, params);
}

void SActionType::parse(INISection* section, ParamCollection* params)
{
	section->readIntValue("Identifier", identifier, atoi(section->getSectionName().c_str()));
	section->readStringValue("Name", name);
	section->readStringValue("Description", description);
	section->readStringValue("ParamString", paramString, "0");
	section->readBoolValue("RequiresAres", requiresAres, false);
	section->readBoolValue("Works", works, true);

	if (paramString == "0")
		return;

	LineSplitter split(paramString);
	if (split.pop(P1))
	{
		if (P1 > 0)
			param = params->get(P1);
	}
	else
	{
		Log::line("Unable to parse Action with ID '" + section->getSectionName() + "', invalid ParamString", Log::DEBUG);
	}

}