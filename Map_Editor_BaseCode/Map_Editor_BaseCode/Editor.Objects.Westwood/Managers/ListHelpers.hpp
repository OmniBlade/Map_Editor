#pragma once
#include "List.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Log.hpp"

template<typename T> 
void findOrAllocateAll(List<T>& list, INISection& section)
{
	//Log::note("Now in findOrAllocateAll()", Log::DEBUG);
	for (const auto& it : section)
	{
		list.findOrAllocate(section.getValue(it));
	}
}

template<typename T>
void loadFromINI(List<T>& list, INIFile& file, INIFile& art)
{
	//Log::note("Now in loadFromINI()", Log::DEBUG);
	for (unsigned int i = 0; i < list.typeList.size(); ++i)
	{
		list.typeList[i].get()->loadRules(&file);
		list.typeList[i].get()->loadArt(&art);
	}

/*	for (const auto& it : list.typeList)
	{
		//Log::line("Now in loading rules...", Log::DEBUG);
		it.get()->loadRules(&file);
		//Log::line("Now in loading art...", Log::DEBUG);
		it.get()->loadArt(&art);
	}*/
}