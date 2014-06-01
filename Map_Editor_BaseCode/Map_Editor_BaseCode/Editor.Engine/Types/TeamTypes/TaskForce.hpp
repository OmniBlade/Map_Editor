#pragma once

#include "../Managers/ObjectList.hpp"
#include "TFEntry.hpp"
#include <string>
#include <vector>
#include <memory>

class INIFile;

class TaskForce
{
public:
	static ObjectList<TaskForce> Array;

	TaskForce(const std::string& id);
	void parse(INIFile* file, bool isGlobal = false);
	std::string ID, Name;
	int Group;
	bool isGlobal;
	std::vector<std::unique_ptr<TFEntry>> unitList;
};

