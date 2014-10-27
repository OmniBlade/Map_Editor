#pragma once

#include "Managers/MapObjectList.hpp"
#include "../Map/Cells/CellStruct.h"
#include <string>

class INIFile;

class Waypoint
{
public:
	static MapObjectList<Waypoint> Array;
	static void writeToINI(INIFile& file);

	Waypoint();
	void parse(const std::string& id, const std::string& list);
	int index;
	std::string ID, Name, letterIndex;
	CellStruct MapCoords;

	int getIndex();
	std::string getLetterIndex();

};

