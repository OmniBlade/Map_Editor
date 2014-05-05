#pragma once

#include <vector>
#include <memory>
#include "ConfigFile.hpp"

class ConfigLoader
{
public:
	ConfigLoader();

	void parse();
	bool chooseConfig();

	std::vector<std::unique_ptr<ConfigFile>> configFiles;
};

