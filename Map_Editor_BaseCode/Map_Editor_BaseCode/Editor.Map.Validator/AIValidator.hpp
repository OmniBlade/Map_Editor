#pragma once

class AITriggerType;

class AIValidator
{
public:
	AIValidator();
	~AIValidator();

	void validateAITrigger();
	void validateAIEnable();

	bool checkTechType(AITriggerType* aiTrigger);
};

