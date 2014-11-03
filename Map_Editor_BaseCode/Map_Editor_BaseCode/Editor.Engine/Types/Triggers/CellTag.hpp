#pragma once

#include "../Managers/MapObjectList.hpp"
#include "../../Map/Cells/CellStruct.h"
#include <string>

class Tag;
class INIFile;

class CellTag
{
public:
	static MapObjectList<CellTag> Array;
	static void writeToINI(INIFile& file);

	CellTag();
	void parse(const std::string& location, const std::string& tag);
	
	std::string Location;// , attachedTag;
	CellStruct MapCoords;
	Tag* pTag;
	bool isGlobal = false;

};

