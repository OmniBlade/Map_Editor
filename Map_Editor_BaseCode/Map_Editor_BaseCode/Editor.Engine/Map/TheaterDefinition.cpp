#include "stdafx.h"
#include "TheaterDefinition.hpp"
#include <iostream>

TheaterDefinition::TheaterDefinition(const std::vector<std::string>& _defaultTheater, INISection* _theaterSection)
:theaterSection(_theaterSection)
{
	if (_defaultTheater.size() >= 10)
		parseTheaterValues(_defaultTheater);
	else
		std::cout << "ERRORS - Default theater values does not have 9 values, unable to parse!" << std::endl;

	//dumpContent();
}

/*Theater::Theater(const std::vector<std::string>* _defaultTheater)
{
	parseTheaterValues(_defaultTheater);
}*/

void TheaterDefinition::parseTheaterValues(const std::vector<std::string>& _defaultTheater)
{
	if (theaterSection == nullptr)// && _defaultTheater != nullptr)
	{
		sectionName = _defaultTheater[0];
		Name = _defaultTheater[1];
		INIFile = _defaultTheater[2];
		ININame = _defaultTheater[3];
		NewTheaterSuffix = _defaultTheater[4];
		TileExtension = _defaultTheater[5];
		MarblePrefix = _defaultTheater[6];
		TerrainPalette = _defaultTheater[7];
		UnitPalette = _defaultTheater[8];
		OverlayPalette = _defaultTheater[9];
	}
	else
	{
		sectionName = theaterSection->getSectionName();

		theaterSection->readStringValue("Name", Name, _defaultTheater[0].c_str());
		theaterSection->readStringValue("INIFileName", INIFile, _defaultTheater[1].c_str());
		theaterSection->readStringValue("ININame", ININame, _defaultTheater[2].c_str());
		theaterSection->readStringValue("NewTheaterSuffix", NewTheaterSuffix, _defaultTheater[3].c_str());
		theaterSection->readStringValue("TileExtension", TileExtension, _defaultTheater[4].c_str());
		theaterSection->readStringValue("MarblePrefix", MarblePrefix, _defaultTheater[5].c_str());
		theaterSection->readStringValue("TerrainPalette", TerrainPalette, _defaultTheater[6].c_str());
		theaterSection->readStringValue("UnitPalette", UnitPalette, _defaultTheater[7].c_str());
		theaterSection->readStringValue("OverlayPalette", OverlayPalette, _defaultTheater[8].c_str());
	}
}

void TheaterDefinition::dumpContent()
{
	std::cout << "\n-------------------------------------------Dumping content for: " << Name << std::endl;
	std::cout << "Name: " << Name << std::endl;
	std::cout << "INIFile: " << INIFile << std::endl;
	std::cout << "ININame: " << ININame << std::endl;
	std::cout << "NewTheater: " << NewTheaterSuffix << std::endl;
	std::cout << "TileExt: " << TileExtension << std::endl;
	std::cout << "Marble: " << MarblePrefix << std::endl;
	std::cout << "Terrain: " << TerrainPalette << std::endl;
	std::cout << "Unit: " << UnitPalette << std::endl;
	std::cout << "Overlay: " << OverlayPalette << std::endl;
}