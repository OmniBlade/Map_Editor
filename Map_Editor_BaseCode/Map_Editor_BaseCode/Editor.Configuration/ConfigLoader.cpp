#include "stdafx.h"
#include "ConfigLoader.hpp"
#include "../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../Editor.FileSystem/IniFile/INISection.hpp"
#include "../Config.hpp"
#include "../Log.hpp"
#include "../GameDefinition.h"
#include <sstream>
#include <iostream>

ConfigLoader::ConfigLoader()
{
	parse();
}

void ConfigLoader::parse()
{
	std::string CONFIG = "CONFIGS";
	INIFile* configINI = INIManager::getManager()->getRoot(CONFIG);

	if (!configINI)
	{
		Log::note("CONFIGS file is missing, unable to continue!", Log::DEBUG);
	}

	Log::note();
	Log::note("Showing global configuration flags below:", Log::DEBUG);
	if (INISection* mainSection = configINI->getSection("Main"))
	{
		mainSection->readBoolValue("InGameLighting", Config::inGameLighting, true);
		mainSection->readBoolValue("FA2Mode", Config::FA2Mode, false);
		mainSection->readBoolValue("AIReferences", Config::AIReferences, false);
	}
	else
	{
		Log::note("Section [Main] (CONFIGS) could not be found! Using defaults.", Log::DEBUG);
		Config::inGameLighting = true;
		Config::FA2Mode = false;
		Config::AIReferences = false;
	}
	Log::note("In-game lighting: " + Log::toString(Config::inGameLighting), Log::DEBUG);
	Log::note("FA2 mode: " + Log::toString(Config::FA2Mode), Log::DEBUG);
	Log::note("AI References: " + Log::toString(Config::AIReferences), Log::DEBUG);
	Log::note();

	INISection* configurations = configINI->getSection("Configurations");
	std::stringstream number;

	for (unsigned int i = 0; i < configurations->size(); ++i)
	{
		number << i;
		INISection* aConfig = configINI->getSection(configurations->getValue(number.str()));
		if (!aConfig)
		{
			Log::note("Configuration entry with name '" + number.str() + "' does not exist as a section!", Log::DEBUG);
			break;
		}

		std::string name, file, path, gameType;
		aConfig->readStringValue("Name", name);
		aConfig->readStringValue("ConfigFile", file);
		aConfig->readStringValue("InstallDir", path);
		aConfig->readStringValue("Game", gameType, "NULL");

		configFiles.push_back(std::make_unique<ConfigFile>(name, file, path, gameType));
		number.str(std::string());
	}
}

bool ConfigLoader::chooseConfig()
{
	if (configFiles.size() == 1)
	{
		Game::title = configFiles.back()->usedTitle;
		Config::installDir = configFiles.back()->InstallDir;
		Config::configName = configFiles.back()->Path;
		Config::parse(INIManager::getManager()->getRoot(configFiles.back().get()->Path));
		return true;
	}
	else if (configFiles.size() > 1)
	{
		std::cout << "\n==================================================================" << std::endl;
		std::cout << "The following configuration files have been found, please select \nthe one you want to use by entering the corresponding number:" << std::endl;
		for (unsigned int i = 0; i < configFiles.size(); ++i)
		{
			std::cout << i << ": " << configFiles[i]->Name << " (" << configFiles[i]->Path << ")" << std::endl;
		}
		unsigned int index = 666;
		std::cout << "Please enter the number of the game you want to load:\n" << std::endl;
		std::cin >> index;

		if (index >= configFiles.size())
			index = 0;
		
		if (configFiles[index].get()->usedTitle == Game::Type::Undefined)
		{
			Log::note("The selected mod is for a game not supported by the editor, unable to continue!", Log::DEBUG);
			return false;
		}

		Game::title = configFiles[index].get()->usedTitle;
		Config::configName = configFiles[index]->Path;
		Config::installDir = configFiles[index]->InstallDir;
		Config::parse(INIManager::getManager()->getRoot(configFiles[index].get()->Path));
		return true;
	}
	Log::note("There are 0 configuration files listed, unable to continue!", Log::DEBUG);
	return false;
}