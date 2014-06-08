#pragma once
#include <string>
#include "ObjectList.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"

template<typename T>
void allocateAll(ObjectList<T>& list, INIFile* iniFile, const std::string& sectionName)
{
	INISection* section = iniFile->getSection(sectionName);
	if (!section) return;

	findOrAllocateAll(list, *section);

}

template<typename T>
void findOrAllocateAll(ObjectList<T>& list, INISection& section)
{
	//Log::note("Now in findOrAllocateAll()", Log::DEBUG);
	for (const auto& it : section)
	{
		list.findOrAllocate(section.getValue(it.c_str()));
	}
}

template<typename T>
void loadAllocatedINI(ObjectList<T>& list, INIFile& file, bool isGlobal = false)
{
	for (unsigned int i = list.lastParsedItem; i < list.objectTypeList.size(); ++i)
	{
		list.objectTypeList[i].get()->parse(&file, isGlobal);
	
	}
	list.lastParsedItem = list.objectTypeList.size();
}

template<typename T>
void loadFromINI(ObjectList<T>& list, INIFile& file, const std::string& section)
{
	INISection* pSection = file.getSection(section);
	if (!pSection) return;

	INISection& uglySection = *pSection;

	for (const auto& it : uglySection)
	{
		list.make();
		list.objectTypeList[list.count() - 1].get()->parse(it, uglySection.getValue(it.c_str()));
	}
}

template<typename T>
void loadAIFromINI(ObjectList<T>& list, INIFile& file, const std::string& section, bool isGlobal = false)
{
	INISection* pSection = file.getSection(section);
	if (!pSection) return;

	INISection& uglySection = *pSection;

	for (const auto& it : uglySection)
	{
		list.make();
		list.objectTypeList[list.count() - 1].get()->parse(it, uglySection.getValue(it.c_str()), isGlobal);
	}
}