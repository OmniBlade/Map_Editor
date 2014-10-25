#pragma once
#include <vector>
#include <string>
#include "../../IniFile/INIFile.hpp"
#include "../../../Editor.Objects.Westwood/Managers/WWList.hpp"

class MapMods
{
public:
	static MapMods* instance();
	static void writeToINI(INIFile& file);

	~MapMods();

	void parse(INIFile* map);

private:
	static MapMods* pInstance;
	MapMods();

	std::string getComparisonValue(const std::string& section, const std::string& key);
	
	void filterNonDifferentMods();
	void writeGenericSections(INIFile& file);
	void writeFoaSections(INIFile& file);

	template <typename T>
	void writeAFoaSection(WWList<T>& list, const std::string& name, INIFile& file)
	{
		auto section = modsFile->getSection(name);
		if (section)
		{
			file.addSectionByCopy(section, true);

			std::string previousValue = name;
			for (const auto& it : section->getKeys())
			{
				auto value = section->getValue(it);
				if (modsFile->sectionExists(value))
				{
					file.addSectionByCopyAfter(previousValue, modsFile->getSection(value.c_str()));
					modsFile->deleteSection(value.c_str());
				}
				previousValue = value;
			}
			modsFile->deleteSection(name.c_str());
		}

		//See if any other is of this type!
		for (const auto& it : modsFile->getSectionList())
		{
			if (list.exists(it))
			{
				file.addSectionByCopyAfter(name, modsFile->getSection(it));
				modsFile->deleteSection(it.c_str());
			}
		}
	}
	
	INIFile* modsFile;
};

