#include "stdafx.h"
#include "Tag.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Log.hpp"
#include "Trigger.hpp"

/* static */ ObjectList<Tag> Tag::Array;

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
		Log::note("Unable to parse Tag with ID '" + ID + "'.", Log::DEBUG);
	}
}
