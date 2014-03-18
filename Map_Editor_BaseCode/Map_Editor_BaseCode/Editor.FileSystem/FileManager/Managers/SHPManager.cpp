#include "stdafx.h"
#include "SHPManager.hpp"
#include "../FileSystem.hpp"

SHPManager::SHPManager()
{
}

SHPManager::~SHPManager()
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