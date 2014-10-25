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
	const int expCount = 0x41;
	const int BaseCount = 0x3B;
	std::vector<std::unique_ptr<SActionType>> actionList;
};