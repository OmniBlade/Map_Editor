#include "stdafx.h"
#include "Config.hpp"
#include <string>

bool handleBoolArguments(const std::string& argStr)
{
	if (argStr == "-DEBUG")
	{
		Config::enableDebug = true;
		return true;
	}
	if (argStr == "-DUMPTYPES")
	{
		Config::dumpTypes = true;
		return true;
	}
	return false;
}

bool handleAssignments(const std::string& argStr)
{
	auto split = argStr.find_first_of('=');
	std::string argType, argValue;
	if (split != std::string::npos)
	{
		argType = argStr.substr(0, split);
		argValue = argStr.substr(split + 1);

		//if (argType == "")
			//SOMETHING = argValue
		if (argType == "-MAPNAME")
		{
			Config::mapName = argValue;
		}

	}
	return false;
}

void handleArguments(int anArgc, _TCHAR* argv[])
{
	for (int i = 0; i < anArgc; ++i)	// Loop through all the arguments and see if '(-)debug' is one of them
	{
		std::wstring argWStr = argv[i];
		std::string argStr(argWStr.begin(), argWStr.end());

		if(!handleBoolArguments(argStr))
			handleAssignments(argStr);
	}
}