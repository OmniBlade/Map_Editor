#pragma once

#include "../../../Editor.Objects.Westwood/Vector2D.hpp"
#include <string>

class Tag;

class CellTag
{
public:
	CellTag(const std::string& location, const std::string& tag);
	void parse();
	
	std::string Location, attachedTag;
	Vector2D loc;
	Tag* tag;


};

