#pragma once

#include <vector>

class Tube
{
public:
	Tube(const std::string& entry);
	void parse(const std::string& entry);

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

