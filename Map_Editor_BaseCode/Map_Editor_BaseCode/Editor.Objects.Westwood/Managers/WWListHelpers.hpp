#pragma once
#include "WWList.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"

template<typename T> 
void findOrAllocateAll(WWList<T>& list, INISection& section)
{
	//Log::line("Now in findOrAllocateAll()", Log::DEBUG);
	for (const auto& it : section.getKeys())
	{
		list.findOrAllocate(section.getValue(it));
	}
}

template<typename T>
void loadFromINI(WWList<T>& list, INIFile& file, INIFile& art)
{
	//Log::line("Now in loadFromINI()", Log::DEBUG);
	for (unsigned int i = 0; i < list.typeList.size(); ++i)
	{
		list.typeList[i]->loadRules(&file);
		list.typeList[i]->loadArt(&art);
	}

/*	for (const auto& it : list.typeList)
	{
		//Log::line("Now in loading rules...", Log::DEBUG);
		it.get()->loadRules(&file);
		//Log::line("Now in loading art...", Log::DEBUG);
		it.get()->loadArt(&art);
	}*/
}

template<typename T>
void loadFromSingleINI(WWList<T>& list, INIFile& file)
{
	for (unsigned int i = 0; i < list.typeList.size(); ++i)
	{
		list.typeList[i]->load(&file);
	}
}