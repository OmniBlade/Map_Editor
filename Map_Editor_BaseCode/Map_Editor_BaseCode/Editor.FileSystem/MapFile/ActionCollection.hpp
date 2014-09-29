#pragma once
#include "ActionType.hpp"
#include <vector>
#include <memory>

class ParamCollection;

class ActionCollection
{
public:
	static ActionCollection* getInstance();

	void parse(ParamCollection* paramColl);
	ActionType* get(int id);

private:
	static ActionCollection* instance;
	ActionCollection();

	ParamCollection* paramColl;
	
	int rBaseCount, rExpCount, count;
	const int BaseCount = 0x82;
	const int expCount = 0x92;
	std::vector<std::unique_ptr<ActionType>> actionList;
};

