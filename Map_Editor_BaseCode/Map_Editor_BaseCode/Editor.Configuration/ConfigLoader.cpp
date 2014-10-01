#include "stdafx.h"
#include "ConfigLoader.hpp"
#include "../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../Editor.FileSystem/FileManager/Managers/EncManager.hpp"
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
	configINI = INIManager::instance()->getRoot(CONFIG);
	if (!configINI)
	{
		configINI = EncManager::instance()->getAsINI(CONFIG);
	}

	if (!configINI)
	{
		Log::line("CONFIGS file is missing, unable to continue!", Log::DEBUG);
	}

	Log::line();
	Log::line("Showing global configuration flags below:", Log::DEBUG);
	if (INISection* mainSection = configINI->getSection("Main"))
	{
		mainSection->readBoolValue("InGameLighting", Config::inGameLighting, true);
		mainSection->readBoolValue("IsModSlave", isModSlave, false);
		mainSection->readBoolValue("FA2Mode", Config::FA2Mode, false);
		mainSection->readBoolValue("AIReferences", Config::AIReferences, false);
		mainSection->readBoolValue("ObsoleteSettings", Config::ObsoleteSettings, false);
	}
	else
	{
		Log::line("Section [Main] (CONFIGS) could not be found! Using defaults.", Log::DEBUG);
		Config::inGameLighting = true;
		Config::FA2Mode = false;
		Config::AIReferences = false;
	}
	Log::line("In-game lighting: " + Log::toString(Config::inGameLighting), Log::DEBUG);
	Log::line("FA2 mode: " + Log::toString(Config::FA2Mode), Log::DEBUG);
	Log::line("AI References: " + Log::toString(Config::AIReferences), Log::DEBUG);
	Log::line("Obsolete settings: " + Log::toString(Config::ObsoleteSettings), Log::DEBUG);
	Log::line();

	INISection* configurations = configINI->getSection("Configurations");
	std::stringstream number;

	for (unsigned int i = 0; i < configurations->size(); ++i)
	{
		number << i;
		if (INISection* aConfig = configINI->getSection(configurations->getValue(number.str())))
		{
			std::string name, file, path, gameType;
			aConfig->readStringValue("Name", name);
			aConfig->readStringValue("ConfigFile", file);
			aConfig->readStringValue("InstallDir", path);
			aConfig->readStringValue("Game", gameType);

			configFiles.push_back(std::make_unique<ConfigFile>(aConfig->getSectionName(), name, file, path, gameType));
			number.str(std::string());
		}
		else
		{
			Log::line("Configuration entry with name '" + number.str() + "' does not exist as a section!", Log::DEBUG);
			break;
		}
	}
}

bool ConfigLoader::chooseConfig()
{
	if (!Config::configName.empty())
	{
		INISection* argModSection = configINI->getSection(Config::configName);
		if (argModSection)
		{
			for (unsigned int i = 0; i < configFiles.size(); ++i)
			{
				if (configFiles[i]->ID == Config::configName)
				{
					Game::title = configFiles[i]->usedTitle;
					Config::installDir = configFiles[i]->InstallDir;
					Config::configName = configFiles[i]->Path;
					Config::parse(INIManager::instance()->getRoot(configFiles[i].get()->Path));
					break;
				}
			}
		}
		return true;
	}
	
	if (configFiles.size() == 1 || isModSlave == true)
	{
		int index = configFiles.size()-1;

		if (isModSlave)
		{
			Log::line();
			Log::line("This editor is supplied along with a mod, only 1 configuration will be loaded!", Log::DEBUG);
			Log::line("Hopefully this is the entry of the mod, otherwise Mr. Professional Modder didn't set his CONFIGS up properly.", Log::EXTRA);
			Log::line();
			index = 0;
		}

		Game::title = configFiles[index]->usedTitle;
		Config::installDir = configFiles[index]->InstallDir;
		Config::configName = configFiles[index]->Path;
		Config::parse(INIManager::instance()->getRoot(configFiles[index].get()->Path));
		return true;
	}
	else if (configFiles.size() > 1)
	{
		std::cout << "\n==================================================================" << std::endl;
		std::cout << "The last digit on the right refers to either Base (0), Expansion (1) or Undefined/Not supported (2)." << std::endl;
		std::cout << "The following configuration files have been found, please select \nthe one you want to use by entering the corresponding number:" << std::endl;
		for (unsigned int i = 0; i < configFiles.size(); ++i)
		{
			std::cout << i << ": " << configFiles[i]->Name << " (" << configFiles[i]->Path << " -- " << (int) configFiles[i]->usedTitle << ")" << std::endl;
		}
		unsigned int index = 666;
		std::cout << "Please enter the number of the game you want to load:\n" << std::endl;
		std::cin >> index;

		if (index >= configFiles.size())
			index = 0;
		
		if (configFiles[index].get()->usedTitle == Game::Type::Undefined)
		{
			Log::line("The selected mod is for a game not supported by the editor, unable to continue!", Log::DEBUG);
			return false;
		}

		Game::title = configFiles[index].get()->usedTitle;
		Config::configName = configFiles[index]->Path;
		Config::installDir = configFiles[index]->InstallDir;
		Config::parse(INIManager::instance()->getRoot(configFiles[index].get()->Path));
		return true;
	}
	Log::line("There are 0 configuration files listed, unable to continue!", Log::DEBUG);
	return false;
}