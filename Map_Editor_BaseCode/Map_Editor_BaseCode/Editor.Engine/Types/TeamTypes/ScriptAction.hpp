#pragma once
#include <string>

class ScriptAction
{
public:
	ScriptAction(const std::string& list);

	int action, parameter;
};

