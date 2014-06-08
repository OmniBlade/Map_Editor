#pragma once

#include "../Managers/ObjectList.hpp"
#include "SubAction.hpp"
#include <string>
#include <vector>
#include <memory>

class Action
{
public:
	static ObjectList<Action> Array;

	Action();
	void parse(const std::string& id, const std::string& list);
	void parseActions();
	
	std::string ID, List;
	unsigned int count;
	std::vector<std::shared_ptr<SubAction>> actionList;

};

