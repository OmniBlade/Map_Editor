#pragma once

#include <map>
#include <memory>
#include "../../PaletteFile/PaletteFile.hpp"

class PALManager
{
public:
	PALManager();
	~PALManager();

	PaletteFile* get(const std::string& fileName);
	PaletteFile* cache(const std::string& fileName);

private:
	std::map<std::string, std::unique_ptr<PaletteFile>> paletteFiles;
};

