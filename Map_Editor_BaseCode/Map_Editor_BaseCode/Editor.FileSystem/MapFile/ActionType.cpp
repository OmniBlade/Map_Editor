#include "stdafx.h"
#include "ActionType.hpp"
#include "ParamCollection.hpp"
#include "ParamType.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../Log.hpp"

ActionType::ActionType(INISection* section, ParamCollection* params)
{
	parse(section, params); 
}

void ActionType::parse(INISection* section, ParamCollection* params)
{
	section->readIntValue("Identifier", identifier, atoi(section->getSectionName().c_str()));
	section->readStringValue("Name", name);
	section->readStringValue("Description", description);
	section->readStringValue("TagCode", tagCode);
	section->readStringValue("ParamString", paramString, "0,0,0,0,0,0,0");
	section->readBoolValue("RequiresAres", requiresAres, false);
	section->readBoolValue("Works", works, true);
	section->readBoolValue("FramesAreSeconds", framesIsSeconds, false);

	if (paramString == "0,0,0,0,0,0,0")
		return;

	LineSplitter split(paramString);
	if (split.pop(P1) && split.pop(P2) && split.pop(P3) && split.pop(P4)
		&& split.pop(P5) && split.pop(P6) && split.pop(P7))
	{
		//Add paramTypes for the specific parameters
		if (P1 > 0)
			paramList.push_back(params->get(P1));
		if (P2 > 0)
			paramList.push_back(params->get(P2));
		if (P3 > 0)
			paramList.push_back(params->get(P3));
		if (P4 > 0)
			paramList.push_back(params->get(P4));
		if (P5 > 0)
			paramList.push_back(params->get(P5));
		if (P6 > 0)
			paramList.push_back(params->get(P6));

		/*
			P7 is a special case!
			In usual cases the input will be a waypoint, that is why P7 is usually a 1
			However, there are certain special cases used by the game:
			If P1 is some value, P7 will be read as a numeric number rather than a waypoint
			which means it has a 'valid' ParamType set rather than 1
			1 is in normal cases either a boolean for 'Yes, it uses a waypoint' or in the 
			special cases resolved as a real ParamType which would become AircraftType
			
			In the example below, if the first number is a -5, -9 or -11: P7 is numeric
			All other cases: P7 is waypoint
			If you're using a waypoint for P7 you MUST set 1 there, otherwise it will not
			recognize P7 to be anything at all (0 means not used, you derp)
			If you're using a numeric value for P7, you can't really do much because it
			is all hardcoded to default game values.
			Nevertheless: you'd have to put a valid ParamType there
			
			For the sake of efficiency, a boolean is used to keep track whether it's
			a waypoint input or number input
			It is default to false, set to true if P1 != -5 && != -9 && != -11
		*/
		switch (P1)
		{
		case -5:
		case -9:
		case -11:
			//5, 9, 11 require a numeric input, thus get the actual ParamType
			if (P7 > 0)
				paramList.push_back(params->get(P7));
			break;
		default:
			//All other cases require waypoint input
			p7Waypoint = true;
		}
	}
	else
	{
		Log::line("Unable to parse Action with ID '" + section->getSectionName() + "', invalid ParamString", Log::DEBUG);
	}

}
