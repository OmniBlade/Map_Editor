#pragma once
#include "ActionTemplate.hpp"
#include <vector>
#include <memory>

class ParamCollection;

class ActionCollection
{
public:
	static ActionCollection* getInstance();

	void parse(ParamCollection* paramColl);
	ActionTemplate* get(int id);

private:
	static ActionCollection* instance;
	ActionCollection();

	ParamCollection* paramColl;
	
	int count;
	const int YRCount = 146; // 0 - 145...
	std::vector<std::unique_ptr<ActionTemplate>> actionList;
};

