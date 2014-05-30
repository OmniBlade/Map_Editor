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

	split.pop(Repeating);
	split.pop(Name);
	std::string trigger = split.pop_string();


}
