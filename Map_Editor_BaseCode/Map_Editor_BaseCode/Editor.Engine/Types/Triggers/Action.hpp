#pragma once

#include "../Managers/MapObjectList.hpp"
#include "SubAction.hpp"
#include <string>
#include <vector>
#include <memory>

class INIFile;

class Action
{
public:
	static MapObjectList<Action> Array;
	static void writeToINI(INIFile& file);

	Action();
	void parse(const std::string& id, const std::string& list);
	void parseActions();
	std::string asString();
	
	bool isGlobal = false;
	std::string ID, List;
	unsigned int count;
	std::vector<std::shared_ptr<SubAction>> actionList;

};

