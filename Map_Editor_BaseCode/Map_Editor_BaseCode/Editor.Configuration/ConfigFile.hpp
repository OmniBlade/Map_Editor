#pragma once

#include <string>

class ConfigFile
{
public:
	ConfigFile(const std::string& name, const std::string& path, const std::string& installDir, bool enc);

	std::string Name, Path, InstallDir;
	bool IsEncTypeConfig = false;
};

