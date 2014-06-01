#pragma once
#include "../Managers/List.hpp"
#include <string>

class INIFile;

class Speech
{
public:
	static List<Speech> Array;
	
	Speech(const std::string& id);
	void load(INIFile* file);
	std::string ID, text;
	bool valid = false;
};

