#include "stdafx.h"
#include "CellTag.hpp"
#include "Tag.hpp"
#include "../../../Log.hpp"
#include <cstdlib>

CellTag::CellTag(const std::string& location, const std::string& tag)
:Location(location), attachedTag(tag)
{
}

void CellTag::parse()
{
	Log::note("Types of CellTag aren't parsed yet!", Log::DEBUG);
	loc.x = atoi(Location.substr(Location.length() - 3, Location.length()).c_str());
	loc.y = atoi(Location.substr(0, Location.length() - 3).c_str());
}
