#pragma once

#include <string>

class Trigger;

class Tag
{
public:
	/*
		Called when a Tag from a map file is added (pre-existing)
		@param id The identifier of this Tag (the characters before the '=' sign)
		@param list The list of parameters for this Tag
	*/
	Tag(const std::string& id, const std::string& list);
	void parse(const std::string& list);

	std::string ID, Name;
	int Repeating;
	Trigger* attachedTrigger;
};

