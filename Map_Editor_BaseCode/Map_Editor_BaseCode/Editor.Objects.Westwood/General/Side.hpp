#pragma once

#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include <vector>

class Side
{
public:
	Side();
	void loadRules(INIFile* file);

	std::vector<std::string> sideList;
};

