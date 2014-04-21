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
	std::string capsName = fileName;
	std::transform(capsName.begin(), capsName.end(), capsName.begin(), ::toupper);

	if (tmpFiles[capsName])
		return tmpFiles[capsName].get();
	else
		return cache(capsName);
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