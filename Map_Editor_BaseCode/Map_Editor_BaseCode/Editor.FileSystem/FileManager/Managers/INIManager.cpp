#include "stdafx.h"
#include "INIManager.hpp"
#include "../../../Config.hpp"
#include <iostream>
#include <algorithm>
#include "../FileSystem.hpp"
#include "../BinaryReader.hpp"
#include "../../../Log.hpp"

/* static */ INIManager* INIManager::manager;
/* static */ INIManager* INIManager::getManager()
{
	if (manager)
		return manager;
	else
		manager = new INIManager();
	
	return manager;
}

INIManager::INIManager()
{

}

INIFile* INIManager::get(const std::string& fileName)
{
	std::string capsName = fileName;
	std::transform(capsName.begin(), capsName.end(), capsName.begin(), ::toupper);
	
	if (iniFiles[capsName])
		return iniFiles[capsName].get();
	else
		return cache(capsName);
}

INIFile* INIManager::cache(const std::string& fileName)
{
	FileProperties props = FileSystem::getFileSystem()->getFile(fileName);
	if (props.reader)
	{
		iniFiles[fileName] = std::make_unique<INIFile>(props);
		Log::note("INI: " + fileName + " succesfully cached.", Log::DEBUG);
		return iniFiles[fileName].get();
	}
	else
		iniFiles[fileName] = nullptr;

	return nullptr;
}