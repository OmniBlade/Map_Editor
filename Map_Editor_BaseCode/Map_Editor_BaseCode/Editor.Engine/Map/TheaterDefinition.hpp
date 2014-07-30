#pragma once

#include <string>
#include <vector>

class INISection;

class TheaterDefinition
{
public:
	TheaterDefinition(const std::vector<std::string>& _defaultTheater, INISection* _theaterSection = nullptr);
	
	/*
		Parses the theater's values
		If the section doesn't exist, the default values from the vector will be used
		Otherwise the section will be read, but the default values are used as fall back
	*/
	void parseTheaterValues(const std::vector<std::string>& _defaultTheater);
	
	/*
		Debug function, dumps the content of the variables of this class in the console
	*/
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

