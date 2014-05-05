#pragma once

#include <string>

class VariableName
{
public:
	VariableName(const std::string& name_, bool state_);

	std::string name;
	bool state;
};

class GlobalVariableName
{
public:
	GlobalVariableName(const std::string& name_);

	std::string name;
};