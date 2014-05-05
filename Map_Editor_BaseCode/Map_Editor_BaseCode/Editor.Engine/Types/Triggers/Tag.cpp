#include "stdafx.h"
#include "Tag.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Log.hpp"
#include "Trigger.hpp"

Tag::Tag(const std::string& id, const std::string& list)
:ID(id)
{
	parse(list);
}

void Tag::parse(const std::string& list)
{
	LineSplitter split(list);

	Log::note("Types of Trigger aren't parsed yet!");
	split.pop(Repeating);
	split.pop(Name);
	std::string trigger = split.pop_string();


}
