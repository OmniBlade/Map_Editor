#pragma once

#include "Managers/MapObjectList.hpp"
#include "../../Editor.Objects.Westwood/Managers/WWList.hpp"
#include <string>

class VariableName
{
public:
	static MapObjectList<VariableName> Array;

	VariableName();
	void parse(const std::string& id, const std::string& list);
	std::string Name, ID;
	bool state;
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