#pragma once

#include "../Managers/ObjectList.hpp"

class Event
{
public:
	static ObjectList<Event> Array;

	Event();
	void parse(const std::string& id, const std::string& list);
};

