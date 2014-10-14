#pragma once
#include <vector>
#include <string>
#include "../IniFile/INIFile.hpp"

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
	INIFile modsFile;
	std::vector<std::string> mapSections;
};

