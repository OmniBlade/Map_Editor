#include "stdafx.h"
#include "PALManager.hpp"
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
	if (paletteFiles[fileName])
		return paletteFiles[fileName].get();
	else
		return cache(fileName);
}

PaletteFile* PALManager::cache(const std::string& fileName)
{
	paletteFiles[fileName] = std::make_unique<PaletteFile>(FileSystem::getFileSystem()->getFile(fileName));
	return paletteFiles[fileName].get();
}