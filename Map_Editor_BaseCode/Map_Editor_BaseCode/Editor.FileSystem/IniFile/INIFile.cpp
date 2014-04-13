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

#include "INIFile.hpp"
#include "INISection.hpp"
#include "CStringHelper.hpp"
#include "../../Config.hpp"
#include "../FileManager/FileSystem.hpp"

INIFile::INIFile(const FileProperties& props)
:iniReader(props.reader)
{
	iniReader->setOffset(props.offset);
	iniReader->setSize(props.size);
	load();
}

INIFile::INIFile(const std::string& _iniName, const std::string& _parentName, __int32 offset, int size)
:isLoaded(false), iniName(_iniName)//, iniReader(Config::MAIN_InstallDir + Config::MAIN_BackSlash + _parentName)
{
	//iniReader = &BinaryReader(binaryFile);
	//std::cout << "Offset from reader: " << iniReader->getOffset() << std::endl;
	load();
}

INIFile::INIFile(const std::string& _iniName, const std::string& _directory)
:isLoaded(false), iniName(_iniName)//, iniReader(_directory + Config::MAIN_BackSlash + _iniName)
{
	//iniReader = &BinaryReader(binaryFile);
	//std::cout << "Offset from reader: " << iniReader.getOffset() << std::endl;
	load();
}

INIFile::INIFile(const std::string& _iniName)
:isLoaded(false), iniName(_iniName)//, iniReader(Config::MAIN_InstallDir + Config::MAIN_BackSlash + _iniName)
{
	//iniReader = &BinaryReader(binaryFile);
	//std::cout << "Offset from reader: " << iniReader->getOffset() << std::endl;
	load();
}


INIFile::~INIFile() {}

void INIFile::load()
{
	std::string currentSection;
	std::string line;

	while (iniReader->checkEOF() == false)
	{
		line = iniReader->readTextLine();
	
		auto comment = line.find_first_of(";");
		if (comment != std::string::npos)
		{
			line = line.substr(0, comment);
		}
		if (line.length())
		{
			line = StringHelper::trim(line);
			//std::cout << "Line: " << line << std::endl;
			if (line.front() == '[' && line.back() == ']')
			{
				// section header
				//Logger::log("\n");
				//Logger::log(line);
				std::string lineSub = line.substr(1, line.length() - 2);
				currentSection = StringHelper::trim(lineSub);
				//std::cout << "SECTION : [" << currentSection << "]" << std::endl;
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
					
					//Ehm, this is no longer needed since only 511 characters are read into the buffer from BinaryReader
					//But a log line in there for ERRORS values might be in place
					/*if(value.length() > 511)
					{
						std::string corrValue = value.substr(0, 511);
						std::string errValue = value.substr(512);

						std::cout << "In section '" << currentSection << "', for key '" << key << "', value is too long, this will be cut off:" <<  std::endl;
						std::cout << errValue << std::endl;
						std::cout << "ERRORS in key '" << key << "', too long:" << std::endl;
						std::cout << "Parsed: " << corrValue << std::endl;
						std::cout << "Cut-off: " << errValue << std::endl;
						value = corrValue;
					}*/

					//std::cout << key << " = " << value << std::endl;

					//Logger::log(key + "."+ value);
					
					//We don't want empty keys to be parsed
					if (value.length())
						SetValue(currentSection, key, value);
				}
			}
		}
	}
	isLoaded = true;
	//std::cout << "Is loaded!" << std::endl;
	//sectionList[currentSection]->dumpContent();
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

std::string& INIFile::getININame()
{
	return iniName;
}