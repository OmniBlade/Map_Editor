#pragma once
#include "../../Editor.Objects.Westwood/Managers/WWListHelpers.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include <string>


/*
	Find or allocates an entire INI section for Westwood Objects (NOT map objects/types)
	@param list The list of objects to find or allocate
	@param iniFile The INI file to read the data from
	@param sectionName The INI section to use for finding and allocating
*/
template<typename T>
void allocateAll(WWList<T>& list, INIFile* iniFile, const std::string& sectionName)
{
	INISection* section = iniFile->getSection(sectionName);
	if (!section) return;

	findOrAllocateAll(list, *section);

}
