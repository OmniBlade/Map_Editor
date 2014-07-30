#include "stdafx.h"
#include "ParamCollection.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Log.hpp"
#include <string>

ParamCollection::ParamCollection()
{
	parse();
	applySpecialCases();
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

void ParamCollection::applySpecialCases()
{
	for (unsigned int i = 0; i < paramList.size(); ++i)
	{
		if (paramList[i]->paramID == 14)	  // TeamTypes (diff global AI and local AI)
			paramList[i]->diffGlobal = true;
		else if (paramList[i]->paramID == 52) // ScriptTypes (diff global AI and local AI)
			paramList[i]->diffGlobal = true;
		else if (paramList[i]->paramID == 57) // TaskForces (diff global AI and local AI)
			paramList[i]->diffGlobal = true;
	}
}

ParamType* ParamCollection::get(int ID)
{
	if (ID < 0 || ID > 0)
		return nullptr;

	for (unsigned int i = 0; i < paramList.size(); ++i)
	{
		if (paramList[i]->paramID == ID)
			return paramList[i].get();
	}
	return nullptr;
}