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
	const int paramCount = 58; // 0 - 57...
	std::vector<std::unique_ptr<ParamType>> paramList;
};
