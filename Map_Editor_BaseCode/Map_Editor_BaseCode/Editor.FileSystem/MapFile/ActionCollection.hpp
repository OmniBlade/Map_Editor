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
	
	int rBaseCount, rExpCount, count;
	const int BaseCount = 130; // 0 - 129...
	const int expCount = 146; // 0 - 145...
	std::vector<std::unique_ptr<ActionTemplate>> actionList;
};

