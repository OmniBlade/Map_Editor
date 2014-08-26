#pragma once

#include <string>
#include "../GameDefinition.h"

class ConfigFile
{
public:
	ConfigFile(const std::string& name, const std::string& path, const std::string& installDir, const std::string& game, bool enc);

	std::string Name, Path, InstallDir;
	bool IsEncTypeConfig = false;
	
	Game::Type usedTitle;
};

