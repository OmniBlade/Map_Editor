#include "stdafx.h"
#include "BaseNode.hpp"


BaseNode::BaseNode(const std::string& buildingType_, int x, int y)
:buildingType(buildingType_)
{
	loc.x = x;
	loc.y = y;
}


