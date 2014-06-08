#pragma once
#include "ActionTemplate.hpp"
#include <vector>
#include <memory>

class ActionCollection
{
public:
	static ActionCollection* getInstance();

	void parse();
	ActionTemplate* get(int id);

private:
	static ActionCollection* instance;
	ActionCollection();
	
	int count;
	const int YRCount = 146; // 0 - 145...
	std::vector<std::unique_ptr<ActionTemplate>> actionList;
};

