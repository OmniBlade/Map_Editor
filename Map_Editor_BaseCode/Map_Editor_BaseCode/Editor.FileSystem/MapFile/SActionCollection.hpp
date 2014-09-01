#pragma once
#include "SActionType.hpp"
#include <vector>
#include <memory>

class ParamCollection;

class SActionCollection
{
public:
	static SActionCollection* getInstance();

	void parse(ParamCollection* paramColl);
	SActionType* get(int id);

private:
	static SActionCollection* instance;
	SActionCollection();

	ParamCollection* paramColl;

	int rBaseCount, rExpCount, count;
	const int expCount = 65; // 0 - 64...
	const int BaseCount = 59; // 0 - 58...
	std::vector<std::unique_ptr<SActionType>> actionList;
};