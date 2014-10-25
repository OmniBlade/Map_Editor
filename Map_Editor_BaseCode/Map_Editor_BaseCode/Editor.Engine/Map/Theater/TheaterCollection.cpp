#include "stdafx.h"
#include "TheaterCollection.hpp"
#include <iostream>
#include <algorithm>
#include "../../../Editor.FileSystem/INIFile/INISection.hpp"
#include "../../../Log.hpp"
#include "../../../GameDefinition.h"

/* static */ TheaterCollection* TheaterCollection::instance;
/* static */ TheaterCollection* TheaterCollection::getInstance()
{
	if (instance)
		return instance;
	else
		instance = new TheaterCollection();

	return instance;
}

void TheaterCollection::initiate(INIFile* _configFile)
{
	configFile = _configFile;
	defTheaterNames.push_back("Temperate");
	defTheaterNames.push_back("Snow");
	defTheaterNames.push_back("Urban");

	if (Game::title == Game::Type::Expansion)
	{
		defTheaterNames.push_back("Desert");
		defTheaterNames.push_back("Lunar");
		defTheaterNames.push_back("NewUrban");
	}
	parseTheaters();
}

TheaterCollection::TheaterCollection()
{
}

TheaterCollection::~TheaterCollection()
{
}

bool TheaterCollection::theaterExists(const std::string& _theaterName)
{
	for (unsigned int i = 0; i < theaters.size(); ++i)
	{
		if (theaters[i].get()->Name == _theaterName)
			return true;
	}
	return false;
}

//God, hardcoding things makes it a lot easier and simpler...
//Creates a theater for the default ones
void TheaterCollection::parseTheaters()
{
	//INISection* theatersSection = configFile->getSection("Theaters");

	for (unsigned int i = 0; i < defTheaterNames.size(); ++i)
	{
		createTheater(defTheaterNames[i]);
	}

	validateTheaterPresence();

	/*
	if (configFile->checkSectionExistance("Theaters"))
	{
		INISection* theatersSection = configFile->getSection("Theaters");
		std::cout << "[Theaters] found, parsing default theaters and modified values." << std::endl;

		for (unsigned int i = 0; i < theatersSection->size(); ++i)
		{
			std::string theaterName = theatersSection->getNextValue();
			std::transform(theaterName.begin(), theaterName.end(), theaterName.begin(), ::toupper);
			if (!theaterExists(theaterName))
			{
				if (std::find(defTheaterNames.begin(), defTheaterNames.end(), theaterName) != defTheaterNames.end())
					createTheater(theaterName); //Found it in the section, parse modified values
				else
					createTheater();
			}
		}
	}
	else
	{
		std::cout << "[Theaters] not found, parsing default theaters and values." << std::endl;
		for (unsigned int i = 0; i < defTheaterNames.size(); ++i)
		{
			if (!theaterExists(defTheaterNames[i]))
				createTheater();
		}
	}*/
}

//Check whether the theater exists as a section and pass it on
void TheaterCollection::createTheater(const std::string& _theaterName)
{
	if (configFile->sectionExists(_theaterName))
	{
		INISection* theaterSection = configFile->getSection(_theaterName);
		theaters.insert(theaters.end(), std::make_unique<TheaterDefinition>(getDefaultValues(_theaterName), theaterSection));
	}
	else
		theaters.insert(theaters.end(), std::make_unique<TheaterDefinition>(getDefaultValues(_theaterName)));
}

void TheaterCollection::validateTheaterPresence()
{
	std::cout << std::endl;
	for (unsigned int i = 0; i < defTheaterNames.size(); ++i)
	{
		bool theaterFound = false;
		for (unsigned int j = 0; j < theaters.size(); ++j)
		{
			if (theaters[j].get()->sectionName == defTheaterNames[i])
			{
				theaterFound = true;
				break;
			}
		}
		if (!theaterFound)
			Log::line("Unable to validate presence of default theater with name '" + defTheaterNames[i] + "'.", Log::DEBUG);
	}
}

std::vector<std::string> TheaterCollection::getDefaultValues(const std::string& _theaterName)
{
	std::vector<std::string> defaultValues;
	defaultValues.reserve(10);

	if (_theaterName == "Temperate")
	{
		defaultValues.push_back("Temperate");
		defaultValues.push_back("Temperate");
		if (Game::title == Game::Type::Base)
			defaultValues.push_back("TEMPERAT.INI");
		else
			defaultValues.push_back("TEMPERATMD.INI");
		defaultValues.push_back("TEMPERATE");
		defaultValues.push_back("T");
		defaultValues.push_back("TEM");
		defaultValues.push_back("MMT");
		defaultValues.push_back("ISOTEMP.PAL");
		defaultValues.push_back("UNITTEM.PAL");
		defaultValues.push_back("TEMPERAT.PAL");
	}
	else if (_theaterName == "Snow")
	{
		defaultValues.push_back("Snow");
		defaultValues.push_back("Snow");
		if (Game::title == Game::Type::Base)
			defaultValues.push_back("SNOW.INI");
		else
			defaultValues.push_back("SNOWMD.INI");
		defaultValues.push_back("SNOW");
		defaultValues.push_back("A");
		defaultValues.push_back("SNO");
		defaultValues.push_back("MMS");
		defaultValues.push_back("ISOSNOW.PAL");
		defaultValues.push_back("UNITSNO.PAL");
		defaultValues.push_back("SNOW.PAL");
	}
	else if (_theaterName == "Urban")
	{
		defaultValues.push_back("Urban");
		defaultValues.push_back("Urban");
		if (Game::title == Game::Type::Base)
			defaultValues.push_back("URBAN.INI");
		else
			defaultValues.push_back("URBANMD.INI");
		defaultValues.push_back("URBAN");
		defaultValues.push_back("U");
		defaultValues.push_back("URB");
		defaultValues.push_back("MMU");
		defaultValues.push_back("ISOURB.PAL");
		defaultValues.push_back("UNITURB.PAL");
		defaultValues.push_back("URBAN.PAL");
	}
	else if (_theaterName == "Desert")
	{
		defaultValues.push_back("Desert");
		defaultValues.push_back("Desert");
		defaultValues.push_back("DESERTMD.INI");
		defaultValues.push_back("DESERT");
		defaultValues.push_back("D");
		defaultValues.push_back("DES");
		defaultValues.push_back("MMD");
		defaultValues.push_back("ISODES.PAL");
		defaultValues.push_back("UNITDES.PAL");
		defaultValues.push_back("DESERT.PAL");
	}
	else if (_theaterName == "Lunar")
	{
		defaultValues.push_back("Lunar");
		defaultValues.push_back("Lunar");
		defaultValues.push_back("LUNARMD.INI");
		defaultValues.push_back("LUNAR");
		defaultValues.push_back("L");
		defaultValues.push_back("LUN");
		defaultValues.push_back("MML");
		defaultValues.push_back("ISOLUN.PAL");
		defaultValues.push_back("UNITLUN.PAL");
		defaultValues.push_back("LUNAR.PAL");
	}
	else if (_theaterName == "NewUrban")
	{
		defaultValues.push_back("NewUrban");
		defaultValues.push_back("New Urban");
		defaultValues.push_back("URBANNMD.INI");
		defaultValues.push_back("NEWURBAN");
		defaultValues.push_back("N");
		defaultValues.push_back("UBN");
		defaultValues.push_back("MMT");
		defaultValues.push_back("ISOUBN.PAL");
		defaultValues.push_back("UNITUBN.PAL");
		defaultValues.push_back("URBANN.PAL");
	}
	//std::cout << "Size of default values: " << defaultValues.size() << std::endl;
	return defaultValues;
}

TheaterDefinition* TheaterCollection::getCurrent()
{
	return currentTheater;
}

TheaterDefinition* TheaterCollection::getByININame(const std::string& name)
{
	for (unsigned int i = 0; i < theaters.size(); ++i)
	{
		if (theaters[i]->ININame == name)
		{
			return theaters[i].get();
		}
	}

	return nullptr;
}

void TheaterCollection::setCurrent(const std::string& theaterName)
{
	for (unsigned int i = 0; i < theaters.size(); ++i)
	{
		if (theaters[i]->ININame == theaterName)
		{
			currentTheater = theaters[i].get();
			break;
		}
	}
}