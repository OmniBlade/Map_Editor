#include "stdafx.h"
#include "CellTag.hpp"
#include "Tag.hpp"
#include "../../../Log.hpp"
#include <cstdlib>

/* static */ ObjectList<CellTag> CellTag::Array;

CellTag::CellTag()
{
}

void CellTag::parse(const std::string& location, const std::string& tag)
{
	Location = location;
	pTag = Tag::Array.find(tag);
	loc.x = atoi(Location.substr(Location.length() - 3, Location.length()).c_str());
	loc.y = atoi(Location.substr(0, Location.length() - 3).c_str());
}
