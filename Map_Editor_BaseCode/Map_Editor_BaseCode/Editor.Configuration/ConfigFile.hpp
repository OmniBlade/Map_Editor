#pragma once

#include <string>
#include "../GameDefinition.h"

class ConfigFile
{
public:
	ConfigFile(const std::string& id, const std::string& name, const std::string& path, const std::string& installDir, const std::string& game);

	std::string ID, Name, Path, InstallDir;
	Game::Type usedTitle;
};

