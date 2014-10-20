#pragma once

#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include <memory>
#include <vector>
#include <map>

class INIFile;

class Side
{
public:
	static Side* instance();
	void loadRules(INIFile* file);
	int getSideIndexByCountry(const std::string& name);
	int getSideIndexByName(const std::string& name);
	std::string getSideName(const std::string& name);

private:
	Side();
	static Side* it;

	std::map<std::string, std::unique_ptr<LineSplitter>> sideList;
	std::vector<std::string> sideKeys;
};

