#pragma once

#include "../Managers/ObjectList.hpp"
#include <string>

class Trigger;

class Tag
{
public:
	static ObjectList<Tag> Array;

	/*
		Called when a Tag from a map file is added (pre-existing)
		@param id The identifier of this Tag (the characters before the '=' sign)
		@param list The list of parameters for this Tag
	*/
	Tag();
	void parse(const std::string& id, const std::string& list);

	std::string ID, Name, trigger;
	int Repeating;
	Trigger* pTrigger;
};

