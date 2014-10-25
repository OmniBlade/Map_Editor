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
	static void writeToINI(INIFile& file, bool flushNames = false);

	ScriptType(const std::string& id);
	void parse(INIFile* file, bool isGlobal = false);
	void writeContentToINI(INIFile& file, bool voidNames = false);
	
	std::string Name, ID;
	bool isGlobal = false;
	std::vector<std::shared_ptr<ScriptAction>> actionList;

};

