#pragma once
#include "SActionTemplate.hpp"
#include <vector>
#include <memory>

class ParamCollection;

class SActionCollection
{
public:
	static SActionCollection* getInstance();

	void parse(ParamCollection* paramColl);
	SActionTemplate* get(int id);

private:
	static SActionCollection* instance;
	SActionCollection();

	ParamCollection* paramColl;

	int count;
	const int YRCount = 65; // 0 - 64...
	std::vector<std::unique_ptr<SActionTemplate>> actionList;
};