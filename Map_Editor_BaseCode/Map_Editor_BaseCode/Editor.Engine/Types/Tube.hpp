#pragma once

#include "Managers/MapObjectList.hpp"
#include <vector>

class INIFile;

class Tube
{
public:
	static MapObjectList<Tube> Array;
	static void writeToINI(INIFile& file);

	Tube();
	void parse(const std::string& id, const std::string& list);
	std::string asString();

	/*
		startX - Starting X-coordinate of the tube
		startY - Starting Y-coordinate of the tube
		direction - The facing the tunnel has, 0-7 (like how SHPs face)
		endX - Ending X-coordinate of the tube
		endY - Ending Y-coordinate of the tube
	*/
	int startX, startY, direction, endX, endY;
	std::string ID;
	std::vector<int> steps;
};

