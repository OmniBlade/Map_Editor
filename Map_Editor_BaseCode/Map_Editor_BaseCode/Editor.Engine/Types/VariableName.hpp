#pragma once

#include "Managers/ObjectList.hpp"
#include <string>

class VariableName
{
public:
	static ObjectList<VariableName> Array;

	VariableName();
	void parse(const std::string& id, const std::string& list);
	std::string name;
	bool state;
};

class GlobalVariableName
{
public:
	GlobalVariableName(const std::string& name_);

	std::string name;
};