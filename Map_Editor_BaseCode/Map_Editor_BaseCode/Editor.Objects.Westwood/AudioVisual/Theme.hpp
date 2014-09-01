#pragma once
#include "../Managers/WWList.hpp"
#include <string>

class INIFile;

class Theme
{
public:
	static WWList<Theme> Array;

	Theme(const std::string& id);
	void load(INIFile* file);
	std::string ID, Name;
	std::wstring WUIName;
	bool valid = false;
};

