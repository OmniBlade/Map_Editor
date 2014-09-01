#include "stdafx.h"
#include "AITriggerEnable.hpp"
#include "AITriggerType.hpp"

/* static */ MapObjectList<AITriggerEnable> AITriggerEnable::Array;

AITriggerEnable::AITriggerEnable()
{

}

void AITriggerEnable::parse(const std::string& id, const std::string& state)
{
	ID = id;

	int ret1 = _strcmpi(state.c_str(), "t");
	int ret2 = _strcmpi(state.c_str(), "y");
	int ret3 = _strcmpi(state.c_str(), "1");

	if (ret1 == 0 || ret2 == 0 || ret3 != 0)
	{
		enabled = false;
	}
	else
	{
		enabled = true;
	}
}

std::string AITriggerEnable::asString()
{
	if (enabled)
	{
		return "yes";
	}
	else
	{
		return "no";
	}
}