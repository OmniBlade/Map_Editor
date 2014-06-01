#pragma once
#include "../Managers/List.hpp"
#include <string>

class INIFile;

class Theme
{
public:
	static List<Theme> Array;

	Theme(const std::string& id);
	void load(INIFile* file);
	std::string ID;
	std::wstring name;
	bool valid = false;
};

