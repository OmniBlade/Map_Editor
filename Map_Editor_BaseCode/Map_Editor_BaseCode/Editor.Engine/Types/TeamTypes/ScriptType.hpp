#pragma once

#include "../Managers/MapObjectList.hpp"
#include <string>
#include <vector>
#include <memory>
#include "ScriptAction.hpp"

class INIFile;

class ScriptType
{
public:
	static MapObjectList<ScriptType> Array;

	ScriptType(const std::string& id);
	void parse(INIFile* file, bool isGlobal = false);
	
	std::string Name, ID;
	bool isGlobal;
	std::vector<std::shared_ptr<ScriptAction>> actionList;

};

