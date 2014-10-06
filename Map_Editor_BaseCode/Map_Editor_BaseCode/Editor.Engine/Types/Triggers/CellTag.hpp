#pragma once

#include "../Managers/MapObjectList.hpp"
#include "../../../Editor.Objects.Westwood/Vector2D.hpp"
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
	Vector2D loc;
	Tag* pTag;


};

