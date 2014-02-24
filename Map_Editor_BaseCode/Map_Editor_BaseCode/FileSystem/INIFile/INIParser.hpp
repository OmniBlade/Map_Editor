#pragma once
class INIParser
{
public:
	INIParser();
	~INIParser();

	void parseBuildingTypes();
	void parseInfantryTypes();
	void parseAircraftTypes();
	void parseUnitTypes();
};

