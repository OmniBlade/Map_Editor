#include "stdafx.h"
#include "BaseNode.hpp"


BaseNode::BaseNode(const std::string& buildingType_, int x, int y)
:buildingType(buildingType_)
{
	loc.x = x;
	loc.y = y;
}

std::string BaseNode::asString()
{
	char buffer[512];
	sprintf_s(buffer, 512, "%s,%d,%d",
		this->buildingType.c_str(),
		this->loc.x,
		this->loc.y
		);

	return buffer;
}


