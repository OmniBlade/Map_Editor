#pragma once

#include <string>

class INIFile;

class ScriptType
{
public:
	ScriptType(const std::string& id);
	void parse(INIFile* file);
	
	std::string Name, ID;



};

