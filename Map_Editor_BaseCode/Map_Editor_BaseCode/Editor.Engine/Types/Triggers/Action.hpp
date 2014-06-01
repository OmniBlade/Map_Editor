#pragma once

#include "../Managers/ObjectList.hpp"
#include <string>

class Action
{
public:
	static ObjectList<Action> Array;

	Action();
	void parse(const std::string& id, const std::string& list);
	std::string ID;

};

