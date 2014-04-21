#include "stdafx.h"
#include "VXLManager.hpp"
#include <algorithm>
#include "../FileSystem.hpp"
#include "../../VoxelFile/VPLFile.hpp"

/* static */ VXLManager* VXLManager::manager;
/* static */ VXLManager* VXLManager::getManager()
{
	if (manager)
		return manager;
	else
		manager = new VXLManager();
	return manager;
}


VXLManager::VXLManager()
{
}

VXLFile* VXLManager::get(const std::string& fileName)
{
	std::string capsName = fileName;
	std::transform(capsName.begin(), capsName.end(), capsName.begin(), ::toupper);

	if (vxlFiles[capsName])
		return vxlFiles[capsName].get();
	else
		return cache(capsName);
}

VXLFile* VXLManager::cache(const std::string& fileName)
{
	vxlFiles[fileName] = std::make_unique<VXLFile>(FileSystem::getFileSystem()->getFile(fileName));
	return vxlFiles[fileName].get();
}

void VXLManager::cacheVPL(const std::string& fileName)
{
	VPLFile::getVPL()->setProperties(FileSystem::getFileSystem()->getFile(fileName));
}