#pragma once
#include "../../IniFile/INISection.hpp"
#include "../../../Editor.Engine/Types/Managers/MapObjectList.hpp"

class INIFile;

class NameFlusherClass
{
public:
	NameFlusherClass();
	~NameFlusherClass();

	static void readAndRestoreFrom(INIFile& namesFile);
	static void writeToFile(INIFile& namesFile);

	template <typename T>
	static void restoreBySection(INISection& section, MapObjectList<T>& objects)
	{
		for (const auto& key : section.getKeys())
		{
			const auto& value = section.getValue(key.c_str());
			objects.find(key)->Name = value;
		}
	}

	template <typename T>
	static void writeByType(INIFile& file, MapObjectList<T>& objects, const std::string& sectionName)
	{
		for (const auto& anObject : objects.objectList)
		{
			if (!anObject->isGlobal)
				file.SetValue(sectionName.c_str(), anObject->ID, anObject->Name);
		}
	}
};

