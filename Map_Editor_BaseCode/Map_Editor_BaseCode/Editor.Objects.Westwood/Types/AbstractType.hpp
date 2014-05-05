#pragma once

#include <string>
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"

class AbstractType
{
public:
	AbstractType(const std::string& id);

	virtual void loadRules(INIFile* rules);
	virtual void loadArt(INIFile* art);

	std::string ID = "";
	std::string Name = "MISSING Name";
	std::string UIName;
	std::wstring WUIName;
	bool valid;
};

