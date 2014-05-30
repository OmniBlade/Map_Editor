#pragma once

#include "../Managers/ObjectList.hpp"

class Action
{
public:
	static ObjectList<Action> Array;

	Action();
	void parse(const std::string& id, const std::string& list);
};

