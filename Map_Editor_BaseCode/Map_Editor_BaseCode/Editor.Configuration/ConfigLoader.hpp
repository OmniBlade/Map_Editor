#pragma once

#include <vector>
#include <memory>
#include "ConfigFile.hpp"

class ConfigLoader
{
public:
	ConfigLoader();

	/*
		Parses the CONFIGS file completely
	*/
	void parse();
	
	/*
		Lets the user choose a mod from the CONFIGS file
		If only 1 exists, that mod will be started
		
		NOTE: THIS ONLY APPLIES TO THE CMD VERSION, ACTUAL VERSION WILL HAVE A PROMPT
	*/
	bool chooseConfig();

	std::vector<std::unique_ptr<ConfigFile>> configFiles;
};

