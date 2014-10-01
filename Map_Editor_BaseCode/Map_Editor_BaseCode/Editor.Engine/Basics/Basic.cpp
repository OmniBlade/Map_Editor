#include "stdafx.h"
#include "Basic.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Config.hpp"

/* static */ Basic* Basic::instance;
/* static */ Basic* Basic::getBasic()
{
	if (instance)
		return instance;
	else
		instance = new Basic();
	return instance;
}

Basic::Basic()
{
}

void Basic::parse()
{
	INIFile* map = INIManager::instance()->get(Config::mapName);
	INISection* basic = map->getSection("Basic");

	basic->readStringValue("Name", name);

	if (name.empty())
	{
		name = "No name";
	}

	basic->readStringValue("Player", player);
}