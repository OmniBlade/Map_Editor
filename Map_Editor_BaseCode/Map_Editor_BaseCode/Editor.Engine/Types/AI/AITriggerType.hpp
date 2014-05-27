#pragma once

#include <string>
class TeamType;

class AITriggerType
{
public:
	AITriggerType(const std::string& id, const std::string& list, bool isGlobal_ = false);
	void parse(const std::string& list);
	std::string asString();
	std::string createParameters();

	std::string id, name, owner, techType, uselessString, parameterString, tt1, tt2;
	int techlevel, aiTriggerType, unknown, side, paramNumber, paramEquation;
	float weight, minWeight, maxWeight;
	bool baseDefense, skirmish, easy, medium, hard;
	TeamType* teamtype1 = nullptr;
	TeamType* teamtype2 = nullptr;
	bool isGlobal;
};

