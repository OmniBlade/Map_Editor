#pragma once

#include "../Managers/MapObjectList.hpp"
#include <string>

class Trigger;
class INIFile;

class Tag
{
public:
	static MapObjectList<Tag> Array;
	static void writeToINI(INIFile& file);

	/*
		Called when a Tag from a map file is added (pre-existing)
		@param id The identifier of this Tag (the characters before the '=' sign)
		@param list The list of parameters for this Tag
	*/
	Tag();
	void parse(const std::string& id, const std::string& list);
	std::string asString();

	std::string ID, Name, trigger;
	int Repeating;
	Trigger* pTrigger;
};

