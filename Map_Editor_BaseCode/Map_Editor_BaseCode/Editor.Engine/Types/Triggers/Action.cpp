#include "stdafx.h"
#include "Action.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"

/* static */ ObjectList<Action> Action::Array;

Action::Action()
{
}

void Action::parse(const std::string& id, const std::string& list)
{
	ID = id;
	List = list;
}

void Action::parseActions()
{
	LineSplitter parts(List);

	count = std::move(parts.pop_int());
	
	while (!parts.empty())
	{
		if (auto sub = SubAction::parse(parts))
		{
			actionList.push_back(sub);
		}
		else
		{
			Log::note("Unable to parse Action with ID '" + ID + "'.", Log::DEBUG);
		}
	}
	if (actionList.size() != count)
	{
		Log::note("Action with ID '" + ID + "' does not have the amount of SubActions it is supposed to have.", Log::DEBUG);
	}
}