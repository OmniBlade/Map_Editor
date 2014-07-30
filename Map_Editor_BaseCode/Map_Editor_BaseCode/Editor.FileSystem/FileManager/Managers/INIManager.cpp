#include "stdafx.h"
#include "INIManager.hpp"
#include <iostream>
#include <algorithm>
#include "../FileSystem.hpp"
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

INIFile* INIManager::getRoot(const std::string& fileName)
{
	std::string capsName = fileName;
	std::transform(capsName.begin(), capsName.end(), capsName.begin(), ::toupper);

	if (iniFiles[capsName])
		return iniFiles[capsName].get();
	else
		return cacheRoot(capsName);
}

INIFile* INIManager::cacheRoot(const std::string& fileName)
{
	FileProperties props = FileSystem::getFileSystem()->getRootFile(fileName);
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

void INIManager::cacheIncluded(const std::string& fileName, INIFile* parent)
{
	FileProperties props = FileSystem::getFileSystem()->getFile(fileName);
	if (props.reader)
	{
		iniFiles[fileName] = std::make_unique<INIFile>(props, parent);
		Log::note("INI: " + fileName + " (include) succesfully cached.", Log::DEBUG);
	}
	else
		iniFiles[fileName] = nullptr;
}

void INIManager::loadIncludeINI(const std::string& fileName, std::vector<std::string>& includes, INIFile* parent)
{
	auto result = std::find(includes.begin(), includes.end(), fileName);
	if (result == includes.end())
	{
		includes.push_back(fileName);
		std::string capsName = fileName;
		std::transform(capsName.begin(), capsName.end(), capsName.begin(), ::toupper);
		cacheIncluded(capsName, parent);
	}
}

void INIManager::insert(const std::string& fileName, INIFile* file)
{
	std::string capsName = fileName;
	std::transform(capsName.begin(), capsName.end(), capsName.begin(), ::toupper);

	if (iniFiles[capsName].get() == nullptr)
	{
		iniFiles[capsName] = std::unique_ptr<INIFile>(file);
	}
		
}