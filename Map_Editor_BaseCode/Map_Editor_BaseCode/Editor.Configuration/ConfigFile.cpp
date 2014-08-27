#include "stdafx.h"
#include "ConfigFile.hpp"
#include "../Log.hpp"


ConfigFile::ConfigFile(const std::string& name, const std::string& path, const std::string& installDir, const std::string& game)
	:Name(name), Path(path), InstallDir(installDir)
{
	/*
		Is this ugly?
		Either way, it's an (originally) editor for Yuri's Revenge: Tiberian Sun and Firestorm are not supported!
		Human specifies RA2 or YR for the tag 'Game=', if the value isn't equal to either of the two lower mentioned games, it is undefined!
		Super crash quit exit happens in ConfigLoader after human chooses the wrong mod
	*/
	if (game == "RA2")
	{
		usedTitle = Game::Type::Base;
	}
	else if (game == "YR")
	{
		usedTitle = Game::Type::Expansion;
	}
	else if (game == "TS" || game == "FS")
	{
		usedTitle = Game::Type::Undefined;
		Log::note("Mod definition with name '" + name + "' is for Tiberian Sun or Firestorm, those aren't supported by this editor!", Log::DEBUG);
	}
	else
	{
		usedTitle = Game::Type::Undefined;
		Log::note("Mod definition with name '" + name + "' is not for Red Alert 2 nor Yuri's Revenge!", Log::DEBUG);
	}
}


