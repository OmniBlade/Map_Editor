#include "stdafx.h"
#include "GameModeCollection.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Config.hpp"
#include "../../Log.hpp"

/* static */ GameModeCollection* GameModeCollection::instance;
/* static */ GameModeCollection* GameModeCollection::getInstance()
{
	if (instance)
		return instance;
	else
		instance = new GameModeCollection();

	return instance;
}

GameModeCollection::GameModeCollection()
{

}

GameModeCollection::~GameModeCollection()
{

}

void GameModeCollection::parse()
{
	//The INI file with the game modes
	INIFile* file = INIManager::instance()->get(Config::modes);
	if (!file)
	{
		return;
	}

	//Load [Battle]
	INISection* battle = file->getSection("Battle");
	if (battle)
	{
		for (const auto &it : *battle)
		{
			modes.push_back(std::make_unique<GameMode>(battle->getValue(it)));
		}
	}

	//Load [Cooperative]
	//Eh... does this only load 1 entry because Cooperative mode is special?
	INISection* coop = file->getSection("Cooperative");
	if (coop)
	{
		for (const auto &it : *coop)
		{
			modes.push_back(std::make_unique<GameMode>(coop->getValue(it)));
		}
	}

	//Load [ManBattle]
	INISection* manbattle = file->getSection("ManBattle");
	if (manbattle)
	{
		for (const auto &it : *manbattle)
		{
			modes.push_back(std::make_unique<GameMode>(manbattle->getValue(it)));
		}
	}

	//Load [FreeForAll]
	INISection* ffa = file->getSection("FreeForAll");
	if (ffa)
	{
		for (const auto &it : *ffa)
		{
			modes.push_back(std::make_unique<GameMode>(ffa->getValue(it)));
		}
	}

	//Load [Unholy]
	INISection* unholy = file->getSection("Unholy");
	if (unholy)
	{
		for (const auto &it : *unholy)
		{
			modes.push_back(std::make_unique<GameMode>(unholy->getValue(it)));
		}
	}

	/*
		Load [Siege]
		Removed until UI does or does not support game type.
		Lol, Westwood reference. Not loading this game mode until there's any confirmation from the Ares people
		Can't load stuff that the game doesn't use... Something about false hope IIRC

	INISection* siege = file->getSection("Siege");
	for (const auto &it : *siege)
	{
		modes.push_back(std::make_unique<GameMode>(siege->getValue(it)));
	}
	*/
}

/*
	Setting the current Game Mode works only when you use the INI Name such as 'battle' or 'cooperative'
*/
void GameModeCollection::setCurrent(const std::string& name)
{
	for (unsigned int i = 0; i < modes.size(); ++i)
	{
		if (modes[i]->iniName == name)
		{
			current = modes[i].get();
			break;
		}
	}
}