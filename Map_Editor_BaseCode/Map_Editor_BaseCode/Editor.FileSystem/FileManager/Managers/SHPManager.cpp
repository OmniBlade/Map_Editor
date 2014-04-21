#include "stdafx.h"
#include "SHPManager.hpp"
#include <algorithm>
#include "../FileSystem.hpp"

/* static */ SHPManager* SHPManager::manager;
/* static */ SHPManager* SHPManager::getManager()
{
	if (manager)
		return manager;
	else
		manager = new SHPManager();
	return manager;
}


SHPManager::SHPManager()
{
}

ShpFile* SHPManager::get(const std::string& fileName)
{
	std::string capsName = fileName;
	std::transform(capsName.begin(), capsName.end(), capsName.begin(), ::toupper);

	if (shpFiles[capsName])
		return shpFiles[capsName].get();
	else
		return cache(capsName);
}

ShpFile* SHPManager::cache(const std::string& fileName)
{
		shpFiles[fileName] = std::make_unique<ShpFile>(FileSystem::getFileSystem()->getFile(fileName));
		return shpFiles[fileName].get();
}