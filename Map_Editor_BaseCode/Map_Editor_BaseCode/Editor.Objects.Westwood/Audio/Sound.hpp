#pragma once
#include "../Managers/List.hpp"
#include <string>

class INIFile;

class Sound
{
public:
	static List<Sound> Array;

	Sound(const std::string& id);
	void load(INIFile* file);
	std::string ID, text;
	bool valid = false;
};

