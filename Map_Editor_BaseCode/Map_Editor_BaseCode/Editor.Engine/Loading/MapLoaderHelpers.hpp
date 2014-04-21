#pragma once
#include "../../Editor.Objects.Westwood/Managers/ListHelpers.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include <string>

template<typename T>
void allocateAll(List<T>& list, INIFile* iniFile, const std::string& sectionName)
{
	INISection* section = iniFile->getSection(sectionName);
	if (!section) return;

	findOrAllocateAll(list, *section);

}