#pragma once

#include "../Managers/MapObjectList.hpp"
#include <string>
class AITriggerType;

class AITriggerEnable
{
public:
	static MapObjectList<AITriggerEnable> Array;

	AITriggerEnable();
	void parse(const std::string& id, const std::string& state);
	std::string asString();

	AITriggerType* aiTrigger;
	std::string ID;
	bool enabled;

};

