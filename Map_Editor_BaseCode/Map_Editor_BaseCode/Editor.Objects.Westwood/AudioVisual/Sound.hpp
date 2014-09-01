#pragma once
#include "../Managers/WWList.hpp"
#include <string>

class INIFile;

class Sound
{
public:
	static WWList<Sound> Array;

	Sound(const std::string& id);
	void load(INIFile* file);
	std::string ID, text, Name;
	std::wstring WUIName;
	bool valid = false;
};

