#pragma once
class TriggerValidator
{
public:
	TriggerValidator();
	~TriggerValidator();

	void validateTags();
	void validateTriggers();
	void validateActions();
	void validateEvents();
	void validateCellTags();
};

