#pragma once
#include "../Managers/WWList.hpp"
#include <string>

class INIFile;

class Speech
{
public:
	static WWList<Speech> Array;
	
	Speech(const std::string& id);
	void load(INIFile* file);
	std::string ID, text, Name;
	std::wstring WUIName;
	bool valid = false;
};

