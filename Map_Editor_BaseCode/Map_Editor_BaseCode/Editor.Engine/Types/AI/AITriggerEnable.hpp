#pragma once

#include "../Managers/MapObjectList.hpp"
#include <string>
class AITriggerType;
class INIFile;

class AITriggerEnable
{
public:
	static MapObjectList<AITriggerEnable> Array;
	static void writeToINI(INIFile& file);

	AITriggerEnable();
	void parse(const std::string& id, const std::string& state);
	std::string asString();

	void assignAITrigger();

	AITriggerType* aiTrigger;
	std::string ID;
	bool enabled;

};

