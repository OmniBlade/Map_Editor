#pragma once

#include <string>

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

	std::string getTagIDFor(const std::string& id);
};

