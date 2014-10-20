#pragma once
#include <vector>
#include <string>
#include "../IniFile/INIFile.hpp"
#include "../../Editor.Objects.Westwood/Managers/WWList.hpp"

class MapMods
{
public:
	static MapMods* instance;
	static void writeToINI(INIFile& file);

	MapMods();
	~MapMods();

	void parse(INIFile* map);
		
	bool isAMapSection(const std::string& sectionName);
	void fillMapSections();
	void addSection(const std::string& sectionName) { mapSections.push_back(sectionName); };
	void addSections(std::vector<std::string>& sections) { mapSections.insert(mapSections.end(), sections.begin(), sections.end()); };

private:
	void writeGenericSections(INIFile& file);
	void writeFoaSections(INIFile& file);

	/* */
	template <typename T>
	void writeAFoaSection(WWList<T>& list, const std::string& name, INIFile& file)
	{
		auto section = modsFile->getSection(name);
		if (section)
		{
			file.addSectionByCopy(section);
			writtenSections.push_back(name);

			for (const auto& it : section->getKeys())
			{
				auto value = section->getValue(it);
				if (modsFile->sectionExists(value))
				{
					file.addSectionByCopy(modsFile->getSection(value.c_str()));
					writtenSections.push_back(value);
				}
			}
		}

		//See if any other is of this type!
		for (const auto& it : modsFile->getSectionList())
		{
			if (list.exists(it) && std::find(writtenSections.begin(), writtenSections.end(), it) == writtenSections.end())
			{
				file.addSectionByCopy(modsFile->getSection(it));
				writtenSections.push_back(it);
			}
		}
	}
	
	INIFile* modsFile;
	std::vector<std::string> writtenSections;
	std::vector<std::string> mapSections;
};

