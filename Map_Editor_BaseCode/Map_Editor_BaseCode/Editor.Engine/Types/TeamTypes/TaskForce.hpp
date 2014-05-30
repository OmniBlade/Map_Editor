#pragma once

#include "../Managers/ObjectList.hpp"
#include <string>

class INIFile;

class TaskForce
{
public:
	static ObjectList<TaskForce> Array;

	TaskForce(const std::string& id);
	void parse(INIFile* file);
	std::string ID, Name;
	int Group;
};

