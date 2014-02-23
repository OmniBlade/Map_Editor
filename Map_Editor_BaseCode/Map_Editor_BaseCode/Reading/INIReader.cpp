/*
 * INIFile.cpp
 *
 *  Created on: 27 nov. 2013
 *      Author: Rik
 *	  Semester: CAR
 */

#include "stdafx.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "INIReader.hpp"
#include "INISection.hpp"
#include "CStringHelper.hpp"

INIFile::INIFile(const std::string &filename)
:isLoaded(false), filePath(filename)
{
	load(filename);
}

INIFile::~INIFile() {}

void INIFile::load(const std::string &filename)
{
	std::ifstream file(filename);

	if (file.is_open())
	{
		std::string currentSection;
		std::string line;
		while (std::getline(file, line))
		{

			auto comment = line.find_first_of(";");
			if (comment != std::string::npos)
			{
				line = line.substr(0, comment);
			}

			if (line.length())
			{
				line = StringHelper::trim(line);
				if (line.front() == '[' && line.back() == ']')
				{
					// section header
					//Logger::log("\n");
					//Logger::log(line);
					std::string lineSub = line.substr(1, line.length() - 2);

					currentSection = StringHelper::trim(lineSub);
				}
				else
				{
					auto split = line.find_first_of('=');
					if (split != std::string::npos)
					{
						std::string lineSub1 = line.substr(0, split);
						std::string lineSub2 = line.substr(split + 1);

						std::string key = StringHelper::trim(lineSub1);
						std::string value = StringHelper::trim(lineSub2);

						if(value.size() > 511)
						{
							std::string corrValue = value.substr(0, 511);
							std::string errValue = value.substr(512);

							std::cout << "In section '" << currentSection << "', for key '" << key << "', value is too long, this will be cut off:" <<  std::endl;
							std::cout << errValue << std::endl;
							std::cout << "Error in key '" << key << "', too long:" << std::endl;
							std::cout << "Parsed: " << corrValue << std::endl;
							std::cout << "Cut-off: " << errValue << std::endl;

							value = corrValue;
						}

						//Logger::log(key + "->"+ value);

						SetValue(currentSection, key, value);
					}
				}
			}
		}
		isLoaded = true;
	}
	else
	{
		std::cout << "File with path '" << filePath << "' could not be opened." << std::endl;
	}
}

void INIFile::SetValue(const std::string &section, const std::string &key, const std::string &value)
{
	if (EnsureSection(section))
	{
		getSection(section)->setValue(key, value);
	}
}

INISection* INIFile::EnsureSection(const std::string &section)
{
	if (auto pSection = getSection(section))
	{
		return pSection;
	}

	auto &ret = sectionList[section];

	ret = std::make_shared<INISection>(section);
	return ret.get();
}

INISection* INIFile::getSection(const std::string &section)
{
	auto it = sectionList.find(section);
	if (it != sectionList.end())
	{
		return it->second.get();
	}
	return nullptr;
}

std::map<std::string, std::shared_ptr<INISection>>* INIFile::getSectionMap()
{
	return &sectionList;
}

bool INIFile::checkSectionExistance(const std::string &section)
{
	if (getSection(section) != nullptr)
	{
		return true;
	}
	return false;
}

bool INIFile::checkSectionExistanceAgain(const std::string &section)
{
	if (getSection(section) != nullptr)
	{
		return true;
	}
	std::cout << "\nFATAL - Section '" << section << "' does not exist!" << std::endl;
	return false;
}

bool INIFile::getLoaded() const
{
	return isLoaded;
}
