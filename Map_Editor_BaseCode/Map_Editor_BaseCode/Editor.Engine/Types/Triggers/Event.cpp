#include "stdafx.h"
#include "Event.hpp"

/* static */ ObjectList<Event> Event::Array;

Event::Event()
{
}

void Event::parse(const std::string& id, const std::string& list)
{
	ID = id;
}