#pragma once

#include "../Managers/ObjectList.hpp"
#include "SubEvent.hpp"
#include <string>
#include <vector>
#include <memory>

class Event
{
public:
	static ObjectList<Event> Array;

	Event();
	void parse(const std::string& id, const std::string& list);
	void parseEvents();

	std::string ID, List;
	unsigned int count;
	std::vector<std::shared_ptr<SubEvent>> eventList;
};

