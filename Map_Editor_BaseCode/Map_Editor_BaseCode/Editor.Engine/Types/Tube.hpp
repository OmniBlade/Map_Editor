#pragma once

#include "Managers/ObjectList.hpp"
#include <vector>

class Tube
{
public:
	static ObjectList<Tube> Array;

	Tube();
	void parse(const std::string& id, const std::string& list);

	/*
		startX - Starting X-coordinate of the tube
		startY - Starting Y-coordinate of the tube
		direction - The facing the tunnel has, 0-7 (like how SHPs face)
		endX - Ending X-coordinate of the tube
		endY - Ending Y-coordinate of the tube
	*/
	int startX, startY, direction, endX, endY;
	std::vector<int> steps;

};

