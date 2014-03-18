#include "stdafx.h"
#include "TMPManager.hpp"
#include "../FileSystem.hpp"

TMPManager::TMPManager()
{

}

TMPManager::~TMPManager()
{
}

TMPFile* TMPManager::get(const std::string& fileName)
{
	if (tmpFiles[fileName])
		return tmpFiles[fileName].get();
	else
		return cache(fileName);
}

TMPFile* TMPManager::cache(const std::string& fileName)
{
	tmpFiles[fileName] = std::make_unique<TMPFile>(FileSystem::getFileSystem()->getFile(fileName));
	return tmpFiles[fileName].get();
}