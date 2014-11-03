#pragma once
#include <string>

struct CustomLat
{
	std::string Name;
	short LATIndex = -1;
	short CTLIndex = -1;
	short MorphableIndex = -1;
	const static unsigned short MAX = 0x10;
	std::string TheaterID[MAX]; //16 theaters with the hardcoded name length
};
