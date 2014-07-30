#pragma once
#include "ParamType.hpp"
#include <vector>
#include <memory>

class ParamCollection
{
public:
	ParamCollection();
	void parse();
	void applySpecialCases();

	ParamType* get(int ID);

private:
	const int paramCount = 57; // 1 - 57...
	std::vector<std::unique_ptr<ParamType>> paramList;
};
