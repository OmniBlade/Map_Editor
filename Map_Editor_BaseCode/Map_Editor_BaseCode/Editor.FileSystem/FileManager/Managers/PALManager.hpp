#pragma once

#include <map>
#include <memory>
#include "../../PaletteFile/PaletteFile.hpp"

class PALManager
{
public:
	static PALManager* instance();

	PaletteFile* get(const std::string& fileName);
	PaletteFile* cache(const std::string& fileName);

private:
	static PALManager* manager;
	PALManager();
	std::map<std::string, std::unique_ptr<PaletteFile>> paletteFiles;
};

