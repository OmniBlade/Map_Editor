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
	std::vector<std::string> getDefaultValues();

	ParamType* get(int ID);

private:
	const int paramCount = 0x3A;
	std::vector<std::unique_ptr<ParamType>> paramList;
};
