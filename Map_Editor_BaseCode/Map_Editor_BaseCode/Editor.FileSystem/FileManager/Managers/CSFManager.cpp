#include "stdafx.h"
#include "CSFManager.hpp"
#include <algorithm>
#include "../FileSystem.hpp"
#include "../../../Log.hpp"

/* static */ CSFManager* CSFManager::manager;
/* static */ CSFManager* CSFManager::getManager()
{
	if (manager)
		return manager;
	else
		manager = new CSFManager();

	return manager;
}

CSFManager::CSFManager()
{

}


CSFFile* CSFManager::get(const std::string& fileName)
{
	std::string capsName = fileName;
	std::transform(capsName.begin(), capsName.end(), capsName.begin(), ::toupper);

	if (csfFiles[capsName])
		return csfFiles[capsName].get();
	else
		return cache(capsName);
}

CSFFile* CSFManager::cache(const std::string& fileName)
{
	FileProperties props = FileSystem::getFileSystem()->getFile(fileName);
	if (props.reader)
	{
		csfFiles[fileName] = std::make_unique<CSFFile>(props);
		Log::note("CSF: " + fileName + " succesfully cached.", Log::DEBUG);
		return csfFiles[fileName].get();
	}
	else
		csfFiles[fileName] = nullptr;

	return nullptr;
}

std::wstring CSFManager::getValue(const std::string& name)
{
	std::wstring value;

	for (const auto& file : csfFiles) 
	{
		if (file.second.get()->get(name, value))
			return value;
	}
	return value = L"<No Name>";
}