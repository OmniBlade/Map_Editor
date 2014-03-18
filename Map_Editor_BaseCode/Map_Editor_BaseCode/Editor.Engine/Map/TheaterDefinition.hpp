#pragma once

#include <string>
#include <vector>
#include "../../Editor.FileSystem/INIFile/INISection.hpp"

class TheaterDefinition
{
public:
	TheaterDefinition(const std::vector<std::string>& _defaultTheater, INISection* _theaterSection = nullptr);
	//Theater(const std::vector<std::string>* _defaultTheater);

	void parseTheaterValues(const std::vector<std::string>& _defaultTheater);
	void dumpContent();

	std::string sectionName;
	std::string Name;
	std::string INIFile;
	std::string ININame;
	std::string TileExtension;
	std::string NewTheaterSuffix;
	std::string MarblePrefix;
	std::string TerrainPalette;
	std::string UnitPalette;
	std::string OverlayPalette;

private:
	INISection* theaterSection;
};

