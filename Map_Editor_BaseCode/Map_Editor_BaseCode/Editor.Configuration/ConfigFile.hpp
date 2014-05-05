#pragma once

#include <string>

class ConfigFile
{
public:
	ConfigFile(const std::string& name, const std::string& path);

	std::string Name;
	std::string Path;
};

