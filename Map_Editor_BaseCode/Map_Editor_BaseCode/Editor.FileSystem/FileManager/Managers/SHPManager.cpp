#include "stdafx.h"
#include "SHPManager.hpp"
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
	if (shpFiles[fileName])
		return shpFiles[fileName].get();
	else
		return cache(fileName);
}

ShpFile* SHPManager::cache(const std::string& fileName)
{
		shpFiles[fileName] = std::make_unique<ShpFile>(FileSystem::getFileSystem()->getFile(fileName));
		return shpFiles[fileName].get();
}