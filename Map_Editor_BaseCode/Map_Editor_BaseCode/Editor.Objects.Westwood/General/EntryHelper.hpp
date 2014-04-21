#pragma once

#include "../Managers/List.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include <string>

template<typename T>
void allocateList(List<T>& list, std::string& types)
{
	//key = types; //Assign the new value to the old value if it exists

	if (types.length() < 2) return;

	//Log::line("Allocating for: " + key, Log::DEBUG);
	LineSplitter split(types);
	for (unsigned int i = 0; i < split.size(); ++i)
	{
		//Log::line(split.peek_string(), Log::DEBUG);
		list.findOrAllocate(split.peekFromIndex_string(i));
	}
}