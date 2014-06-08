#pragma once

#include <string>
#include <vector>

class TeamValidator
{
public:
	TeamValidator();
	~TeamValidator();

	void validateScriptType();
	void validateTaskForce();
	void validateTeamType();
	bool validateMPOwner(const std::string& owner);

	std::vector<std::string> mpCountries;
};

