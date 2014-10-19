#include "stdafx.h"
#include "EncManager.hpp"
#include <algorithm>
#include "../FileSystem.hpp"
#include "INIManager.hpp"
#include "../../../Log.hpp"
//#include "../../IniFile/INIFile.hpp"

/* static */ EncManager* EncManager::manager;
/* static */ EncManager* EncManager::instance()
{
	if (manager)
		return manager;
	else
		manager = new EncManager();
	return manager;
}


EncManager::EncManager()
{
}

EncFile* EncManager::get(const std::string& fileName)
{
	std::string capsName = fileName;
	std::transform(capsName.begin(), capsName.end(), capsName.begin(), ::toupper);

	if (encFiles[capsName])
		return encFiles[capsName].get();
	else
		return cache(capsName);
}

EncFile* EncManager::cache(const std::string& fileName)
{
	encFiles[fileName] = std::make_unique<EncFile>(FileSystem::getFileSystem()->getRootFile(fileName), fileName);
	Log::line("ENC: " + fileName + " succesfully cached.", Log::DEBUG);
	return encFiles[fileName].get();
}

INIFile* EncManager::getAsINI(const std::string& fileName)
{
	std::string capsName = fileName;
	std::transform(capsName.begin(), capsName.end(), capsName.begin(), ::toupper);

	if (INIManager::instance()->exists(capsName))
		return INIManager::instance()->get(capsName);
	else
		return cacheAsINI(capsName);
}

INIFile* EncManager::cacheAsINI(const std::string& fileName)
{
	encFiles[fileName] = std::make_unique<EncFile>(FileSystem::getFileSystem()->getRootFile(fileName), fileName);
	Log::line("ENC: " + fileName + " succesfully cached.", Log::DEBUG);
	return INIManager::instance()->get(fileName);
}
