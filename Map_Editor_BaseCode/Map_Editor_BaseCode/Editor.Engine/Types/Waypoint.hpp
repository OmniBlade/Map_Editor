#pragma once

#include "Managers/ObjectList.hpp"
#include "../../Editor.Objects.Westwood/Vector2D.hpp"
#include <string>

class Waypoint
{
public:
	static ObjectList<Waypoint> Array;

	Waypoint();
	void parse(const std::string& id, const std::string& list);
	int index;
	std::string ID, letterIndex;
	Vector2D loc;

	int getIndex();
	std::string getLetterIndex();

};

