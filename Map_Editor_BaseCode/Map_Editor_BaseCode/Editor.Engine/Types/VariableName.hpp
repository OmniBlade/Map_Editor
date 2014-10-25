#pragma once

#include "Managers/MapObjectList.hpp"
#include <string>

class INIFile;

class VariableName
{
public:
	static MapObjectList<VariableName> Array;
	static void writeToINI(INIFile& file, bool flushNames = false);

	VariableName();
	void parse(const std::string& id, const std::string& list);
	std::string asString(bool voidName = false);
	std::string Name, ID;
	bool state, isGlobal = false;
};

class GlobalVariableName
{
public:
	static MapObjectList<GlobalVariableName> Array;

	GlobalVariableName();
	void parse(const std::string& id, const std::string& name_);
	std::string Name, ID;
	std::wstring WUIName;
};