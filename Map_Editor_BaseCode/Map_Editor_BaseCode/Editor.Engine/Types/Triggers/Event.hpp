#pragma once

#include "../Managers/ObjectList.hpp"
#include <string>

class Event
{
public:
	static ObjectList<Event> Array;

	Event();
	void parse(const std::string& id, const std::string& list);

	std::string ID;
};

