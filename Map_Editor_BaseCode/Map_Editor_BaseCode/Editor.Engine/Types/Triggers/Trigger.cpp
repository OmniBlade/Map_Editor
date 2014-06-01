#include "stdafx.h"
#include "Trigger.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Log.hpp"
#include "Tag.hpp"
#include "Action.hpp"
#include "Event.hpp"
#include "../../../Editor.Objects.Westwood/Types/Country.hpp"

/* static */ ObjectList<Trigger> Trigger::Array;

Trigger::Trigger()
{
}

void Trigger::parse(const std::string& id, const std::string& list)
{
	ID = id;
	LineSplitter split(list);

	if (split.pop(owner) && split.pop(child) && split.pop(Name) && split.pop(Disabled) && split.pop(EasyEnabled)
		&& split.pop(MedEnabled) && split.pop(HardEnabled) && split.pop(Unknown))
	{
		pOwner = Country::Array.find(owner);
		pActions = Action::Array.find(ID);
		pEvents = Event::Array.find(ID);
	}
	else
	{
		Log::note("Unable to parse Trigger with ID '" + ID + "'.", Log::DEBUG);
	}

}

void Trigger::assignChild()
{
	if (child != "<None>")
	{
		pChild = Trigger::Array.find(child);
	}
}