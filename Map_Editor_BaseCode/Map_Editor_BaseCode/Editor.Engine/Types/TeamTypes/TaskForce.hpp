#pragma once

#include "../Managers/MapObjectList.hpp"
#include "TFEntry.hpp"
#include <string>
#include <vector>
#include <memory>

class INIFile;

class TaskForce
{
public:
	static MapObjectList<TaskForce> Array;
	static void writeToINI(INIFile& file);

	TaskForce(const std::string& id);
	void parse(INIFile* file, bool isGlobal = false);
	void writeContentToINI(INIFile& file);

	std::string ID, Name;
	int Group;
	bool isGlobal;
	std::vector<std::unique_ptr<TFEntry>> unitList;
};

