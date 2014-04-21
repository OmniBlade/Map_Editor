#include "stdafx.h"
#include "PALManager.hpp"
#include <algorithm>
#include "../FileSystem.hpp"

/* static */ PALManager* PALManager::manager;
/* static */ PALManager* PALManager::getManager()
{
	if (manager)
		return manager;
	else
		manager = new PALManager();
	return manager;
}


PALManager::PALManager()
{
}

PaletteFile* PALManager::get(const std::string& fileName)
{
	std::string capsName = fileName;
	std::transform(capsName.begin(), capsName.end(), capsName.begin(), ::toupper);

	if (paletteFiles[capsName])
		return paletteFiles[capsName].get();
	else
		return cache(capsName);
}

PaletteFile* PALManager::cache(const std::string& fileName)
{
	paletteFiles[fileName] = std::make_unique<PaletteFile>(FileSystem::getFileSystem()->getFile(fileName));
	return paletteFiles[fileName].get();
}