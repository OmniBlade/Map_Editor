#pragma once

#include <string>
#include "../GameDefinition.h"

class ConfigFile
{
public:
	ConfigFile(const std::string& name, const std::string& path, const std::string& installDir, const std::string& game);

	std::string Name, Path, InstallDir;
	Game::Type usedTitle;
};

