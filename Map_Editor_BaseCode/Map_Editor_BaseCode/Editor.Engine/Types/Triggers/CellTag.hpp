#pragma once

#include "../Managers/ObjectList.hpp"
#include "../../../Editor.Objects.Westwood/Vector2D.hpp"
#include <string>

class Tag;

class CellTag
{
public:
	static ObjectList<CellTag> Array;
	CellTag();
	void parse(const std::string& location, const std::string& tag);
	
	std::string Location, attachedTag;
	Vector2D loc;
	Tag* tag;


};

