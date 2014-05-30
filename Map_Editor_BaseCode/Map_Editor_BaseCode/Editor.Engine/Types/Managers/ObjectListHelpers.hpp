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
		list.findOrAllocate(section.getValue(it));
	}
}

template<typename T>
void loadAllocatedINI(ObjectList<T>& list, INIFile& file)
{
	for (unsigned int i = 0; i < list.objectTypeList.size(); ++i)
	{
		list.objectTypeList[i].get()->parse(&file);
	}
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
		list.objectTypeList[list.count() - 1].get()->parse(it, uglySection.getValue(it));
	}
}