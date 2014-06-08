#pragma once
#include <string>

class INISection;

class ParamType
{
public:
	ParamType(int paramID_, const std::string& name_);

	int paramID = 0;
	std::string name;
};

