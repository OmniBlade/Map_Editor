#include "stdafx.h"
#include "Tag.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../../Log.hpp"
#include "Trigger.hpp"

/* static */ MapObjectList<Tag> Tag::Array;

Tag::Tag()
{

}

void Tag::parse(const std::string& id, const std::string& list)
{
	ID = id;
	LineSplitter split(list);
	
	if (split.pop(Repeating) && split.pop(Name) && split.pop(trigger))
	{
		pTrigger = Trigger::Array.find(trigger);
	}
	else
	{
		Log::line("Unable to parse Tag with ID '" + ID + "'.", Log::DEBUG);
	}
}

void Tag::writeToINI(INIFile& file)
{
	for (auto& it : Array.objectList)
	{
		file.SetValue("Tags", it->ID, it->asString());
	}
}

std::string Tag::asString()
{
	char buffer[512];
	sprintf_s(buffer, 512, "%d,%s,%s",
		this->Repeating,
		this->Name.c_str(),
		this->pTrigger->ID.c_str()
		);

	return buffer;
}