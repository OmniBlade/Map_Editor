#include "stdafx.h"
#include "CSFManager.hpp"
#include <algorithm>
#include "../FileSystem.hpp"
#include "../../../Log.hpp"
#include "../../../Config.hpp"

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
	std::string capsName = std::move(fileName);
	std::transform(capsName.begin(), capsName.end(), capsName.begin(), ::toupper);

	//if (csfFiles[capsName])
		//return csfFiles[capsName].get();
	//else
		return cache(capsName);
}

CSFFile* CSFManager::cache(const std::string& fileName)
{

	FileProperties props = FileSystem::getFileSystem()->getFile(fileName);
	if (props.reader)
	{
		csfFiles.push_back(std::make_unique<CSFFile>(props));
		Log::line("CSF: " + fileName + " succesfully cached.", Log::DEBUG);
		return csfFiles.back().get();
	}

	return nullptr;
}

std::wstring CSFManager::getValue(const std::string& name)
{
	std::wstring value;

	if (Config::hasAres && name.substr(0, 6) == "NOSTR:")
	{
		std::string& UINameNOSTR = name.substr(6);
		value.assign(UINameNOSTR.begin(), UINameNOSTR.end());
		return value;
	}

	for (const auto& file : csfFiles) 
	{
		if (file.get()->get(name, value))
		{
			return value;
		}
	}
	return value = L"<No Name>";
}