#pragma once

#include <string>

class Waypoint
{
public:
	Waypoint(int index_);

	int index;
	std::string letterIndex;

	int getIndex();
	std::string getLetterIndex();

};

