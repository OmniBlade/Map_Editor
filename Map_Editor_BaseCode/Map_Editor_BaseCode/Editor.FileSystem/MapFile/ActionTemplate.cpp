#include "stdafx.h"
#include "ActionTemplate.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../Log.hpp"

ActionTemplate::ActionTemplate(INISection* section)
{
	parse(section); 
}

void ActionTemplate::parse(INISection* section)
{
	section->readIntValue("Identifier", identifier, atoi(section->getSectionName().c_str()));
	section->readStringValue("Name", name);
	section->readStringValue("Description", description);
	section->readStringValue("TagCode", tagCode);
	section->readStringValue("ParamString", paramString, "0,0,0,0,0,0,0");
	section->readBoolValue("RequiresAres", requiresAres, false);
	section->readBoolValue("Works", works, true);

	if (paramString == "0,0,0,0,0,0,0")
		return;

	LineSplitter split(paramString);
	if (split.pop(P1) && split.pop(P2) && split.pop(P3) && split.pop(P4)
		&& split.pop(P5) && split.pop(P6) && split.pop(P7))
	{

	}
	else
	{
		Log::note("Unable to parse Action with ID '" + section->getSectionName() + "', invalid ParamString", Log::DEBUG);
	}

}
