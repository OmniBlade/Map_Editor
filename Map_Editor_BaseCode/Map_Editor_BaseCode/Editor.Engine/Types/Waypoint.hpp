#pragma once

#include "Managers/MapObjectList.hpp"
#include "../../Editor.Objects.Westwood/Vector2D.hpp"
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
	Vector2D loc;

	int getIndex();
	std::string getLetterIndex();

};

