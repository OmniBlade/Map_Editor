#include "stdafx.h"
#include "Action.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"

/* static */ MapObjectList<Action> Action::Array;

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
			Log::line("Unable to parse Action with ID '" + ID + "'.", Log::DEBUG);
		}
	}
	if (actionList.size() != count)
	{
		Log::line("Action with ID '" + ID + "' does not have the amount of SubActions it is supposed to have.", Log::DEBUG);
	}
}

void Action::writeToINI(INIFile& file)
{
	if (Array.objectList.size() == 0)
	{
		Log::line("SECTION - Actions does not exist, will not write to map.", Log::DEBUG);
		return;
	}

	for (auto& it : Array.objectList)
	{
		file.SetValue("Actions", it->ID, it->asString());
	}
}

std::string Action::asString()
{
	std::string params;
	
	for (auto& it : actionList)
	{
		params.append(it->asString());
	}

	char buffer[512];
	sprintf_s(buffer, 512, "%d%s",
		this->count,
		params.c_str()
		);

	return buffer;

}