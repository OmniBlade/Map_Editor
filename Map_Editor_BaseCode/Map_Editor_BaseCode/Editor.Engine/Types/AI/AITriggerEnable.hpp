#pragma once

#include <string>
class AITriggerType;

class AITriggerEnable
{
public:
	AITriggerEnable(const std::string& id, const std::string& state);
	void parse(const std::string& state);
	std::string asString();

	AITriggerType* aiTrigger;
	std::string id;
	bool enabled;

};

