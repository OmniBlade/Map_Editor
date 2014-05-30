#pragma once

#include "../Managers/ObjectList.hpp"
#include <string>
class AITriggerType;

class AITriggerEnable
{
public:
	static ObjectList<AITriggerEnable> Array;

	AITriggerEnable();
	void parse(const std::string& id, const std::string& state);
	std::string asString();

	AITriggerType* aiTrigger;
	std::string ID;
	bool enabled;

};

