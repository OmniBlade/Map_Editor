#pragma once
#include <string>
#include "MapObjectList.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"

template<typename T>
void allocateAll(MapObjectList<T>& list, INIFile* iniFile, const std::string& sectionName)
{
	INISection* section = iniFile->getSection(sectionName);
	if (!section) return;

	findOrAllocateAll(list, *section);

	if (!iniFile->getSection(sectionName)->size())
	{
		iniFile->deleteSection(sectionName.c_str());
	}
}

template<typename T>
void findOrAllocateAll(MapObjectList<T>& list, INISection& section)
{
	//Log::line("Now in findOrAllocateAll()", Log::DEBUG);
	for (const auto& it : section.getKeys())
	{
		list.findOrAllocate(section.getDeletableValue(it.c_str()));
	}
}

template<typename T>
void loadAllocatedINI(MapObjectList<T>& list, INIFile& file, bool isGlobal = false)
{
	for (unsigned int i = list.lastParsedItem; i < list.objectList.size(); ++i)
	{
		list.objectList[i].get()->parse(&file, isGlobal);
	
	}
	list.lastParsedItem = list.objectList.size();
}

template<typename T>
void loadFromINI(MapObjectList<T>& list, INIFile& file, const std::string& section)
{
	INISection* pSection = file.getSection(section);
	if (!pSection) return;

	for (const auto& it : pSection->getKeys())
	{
		list.make();
		list.objectList[list.count() - 1].get()->parse(it, pSection->getDeletableValue(it.c_str()));
	}

	if (!file.getSection(section)->size())
	{
		file.deleteSection(section.c_str());
	}
}

template<typename T>
void loadAIFromINI(MapObjectList<T>& list, INIFile& file, const std::string& section, bool isGlobal = false)
{
	INISection* pSection = file.getSection(section);
	if (!pSection) return;

	for (const auto& it : pSection->getKeys())
	{
		list.make();
		list.objectList[list.count() - 1].get()->parse(it, pSection->getDeletableValue(it.c_str()), isGlobal);
	}
}