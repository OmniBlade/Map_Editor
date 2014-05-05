#pragma once

#include <string>

class INIFile;

class TaskForce
{
public:
	TaskForce(const std::string& id);
	void parse(INIFile* file);
	std::string ID, Name;
	int Group;
};

