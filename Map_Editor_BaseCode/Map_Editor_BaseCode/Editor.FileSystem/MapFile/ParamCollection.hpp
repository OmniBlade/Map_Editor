#pragma once
#include "ParamType.hpp"
#include <vector>
#include <memory>

class ParamCollection
{
public:
	static ParamCollection* getInstance();

	void parse();

private:
	static ParamCollection* instance;
	ParamCollection();

	const int paramCount = 56; // 1 - 56...
	std::vector<std::unique_ptr<ParamType>> paramList;
};
