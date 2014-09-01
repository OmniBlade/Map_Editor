#pragma once

#include "../Managers/WWList.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include <string>
#include <iostream>

template<typename T>
void allocateList(WWList<T>& list, std::string& types)
{
	//key = types; //Assign the new value to the old value if it exists

	//std::cout << "Hey there! It says here that if types.length() < 2 it should return, but what happens to it if there is only 1?" << std::endl;
	if (types.length() == 1)
	{
		//As far as I can tell, the game takes the entire line if there is only supposed to be 1 entry
		list.findOrAllocate(types);
		return;
	}

	//Log::line("Allocating for: " + key, Log::DEBUG);
	LineSplitter split(types);
	for (unsigned int i = 0; i < split.size(); ++i)
	{
		//Log::line(split.peek_string(), Log::DEBUG);
		list.findOrAllocate(split.peekFromIndex_string(i));
	}
}