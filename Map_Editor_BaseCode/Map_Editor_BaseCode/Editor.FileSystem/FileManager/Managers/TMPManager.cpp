#include "stdafx.h"
#include "TMPManager.hpp"
#include <algorithm>
#include "../FileSystem.hpp"

/* static */ TMPManager* TMPManager::manager;
/* static */ TMPManager* TMPManager::getManager()
{
	if (manager)
		return manager;
	else
		manager = new TMPManager();
	return manager;
}

TMPManager::TMPManager()
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
	FileProperties props = FileSystem::getFileSystem()->getFile(fileName);
	if (props.reader)
	{
		tmpFiles[fileName] = std::make_unique<TMPFile>(props);
		return tmpFiles[fileName].get();
	}
	else
		return nullptr;
}