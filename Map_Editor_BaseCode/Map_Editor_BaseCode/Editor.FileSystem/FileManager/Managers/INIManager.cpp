#include "stdafx.h"
#include "INIManager.hpp"
#include "../../../Config.hpp"
#include <iostream>
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
	if (iniFiles[fileName])
		return iniFiles[fileName].get();
	else
		return cache(fileName);
}

INIFile* INIManager::cache(const std::string& fileName)
{
	FileProperties props = FileSystem::getFileSystem()->getFile(fileName);
	if (props.reader)
	{
		iniFiles[fileName] = std::make_unique<INIFile>(props);
		Log::line("INI: " + fileName + " succesfully cached.", Log::DEBUG);
		return iniFiles[fileName].get();
	}
	else
		iniFiles[fileName] = nullptr;

	return nullptr;
}