#pragma once
#include <string>

class INISection;

class ParamType
{
public:
	ParamType(int paramID_, const std::string& name_, int maxList = 0);

	int paramID = 0, listIndex = 0;
	bool diffGlobal = false;
	std::string name;
};

