#pragma once

#include "../Managers/ObjectList.hpp"
#include <string>

class INIFile;

class ScriptType
{
public:
	static ObjectList<ScriptType> Array;

	ScriptType(const std::string& id);
	void parse(INIFile* file);
	
	std::string Name, ID;



};

