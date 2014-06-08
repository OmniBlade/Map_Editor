#include "stdafx.h"
#include "ParamCollection.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Log.hpp"
#include <string>

/* static */ ParamCollection* ParamCollection::instance;
/* static */ ParamCollection* ParamCollection::getInstance()
{
	if (instance)
		return instance;
	else
		instance = new ParamCollection();

	return instance;
}

ParamCollection::ParamCollection()
{

}

void ParamCollection::parse()
{
	INIFile* file = INIManager::getManager()->getRoot("PARAMS");
	INISection* params = file->getSection("ParamTypes");

	for (int i = 1; i < paramCount; ++i)
	{
		if (params->checkKeyExistance(Log::toString(i)))
			paramList.push_back(std::make_unique<ParamType>(i, params->getValue(Log::toString(i))));
		else
		{
			//Because the list is hardcoded, we can easily insert a missing name
			paramList.push_back(std::make_unique<ParamType>(i, "MISSING"));
			Log::note("ParamType expected at index " + Log::toString(i) + " is not found, inserting dummy instead.", Log::DEBUG);
		}
	}
}