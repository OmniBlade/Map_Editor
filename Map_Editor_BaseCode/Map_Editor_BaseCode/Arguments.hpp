#include "stdafx.h"
#include "Config.hpp"
#include <string>

/*
	The function that is called when boolean type arguments are read
	Usually only concerns 'switches'
	@param argStr The argument to read / parse
	@return True if it is a bool argument, false if not
*/
bool handleBoolArguments(const std::string& argStr)
{
	if (argStr == "-DEBUG")
	{
		Config::enableDebug = true;
		return true;
	}
	/*
		This argument will be moved to debug.log
		Reason is that output.log will be used solely for validation
		Dumping the types will happen AFTER everything is parsed for a map, user wants a ton of shit, user gets a ton of shit
	*/
	if (argStr == "-DUMPTYPES")
	{
		Config::dumpTypes = true;
		return true;
	}
	return false;
}

/*
	Splits the assignment type arguments and parses the value
	Looks for the first = character, then checks what kind of argument type it is and finally
	writes the value to the proper variable
	
	@param argStr The entire argument that will be split and parsed
*/
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
		else if (argType == "-MODNAME")
		{
			//Hah, confusion. Takes the ID of the mod, not the actual file (Yuri's Revenge --> YR, not CONFIG_YR)
			Config::configName = argValue;
		}

	}
	return false;
}

/*
	Loop through all given arguments and parse them
	If the type is not a bool-argument (if it exists, something is set to true), it will be checked for
	an assignment argument (such as map name)
	
	@param anArgc The amount of arguments given
	@param argv The array of actual arguments
*/
void handleArguments(int anArgc, _TCHAR* argv[])
{
	for (int i = 0; i < anArgc; ++i)
	{
		std::wstring argWStr = argv[i];
		std::string argStr(argWStr.begin(), argWStr.end());

		if(!handleBoolArguments(argStr))
			handleAssignments(argStr);
	}
}