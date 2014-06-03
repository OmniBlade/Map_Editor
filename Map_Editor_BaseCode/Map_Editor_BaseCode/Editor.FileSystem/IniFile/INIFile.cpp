/*
 * INIFile.cpp
 *
 *  Created on: 27 nov. 2013
 *      Author: Rik
 *	  Semester: CAR
 */

#include "stdafx.h"
#include "CStringHelper.hpp"
#include "../../Config.hpp"
#include "../FileManager/FileSystem.hpp"
#include "../FileManager/BinaryReader.hpp"
#include "../FileManager/Managers/INIManager.hpp"
#include "../../Log.hpp"

INIFile::INIFile(const FileProperties& props)
:iniReader(props.reader)
{
	iniReader->setOffset(props.offset);
	iniReader->setSize(props.size);
	load(this);
}

INIFile::INIFile(const FileProperties& props, INIFile* parentINI)
:iniReader(props.reader)
{
	iniReader->setOffset(props.offset);
	iniReader->setSize(props.size);
	load(parentINI);
}

void INIFile::load(INIFile* parentINI)
{
	std::string currentSection;
	std::string line;

	Log::timerStart();

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
				//Fuck INI inheritance!
				std::string& preLineSub = line;
				std::size_t found = line.find_first_of("]");
				if (found != std::string::npos)
				{
					preLineSub = line.substr(0, found + 1);
				}

				// section header
				std::string lineSub = preLineSub.substr(1, preLineSub.length() - 2);
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
					
					if(value.length() > 511)
					{
						std::string corrValue = value.substr(0, 511);
						std::string errValue = value.substr(512);

						Log::note("Key '" + key + "' in section '" + currentSection + "' is too long (longer than 512 characters):", Log::DEBUG);
						Log::note("Parsed: " + corrValue, Log::EXTRA);
						Log::note("Cut-off: " + errValue, Log::EXTRA);
						value = corrValue;
					}
					
					//We don't want empty keys to be parsed
					if (value.length())
					{
						if (Config::hasAres && currentSection == "#include")
						{
							INIManager::getManager()->loadIncludeINI(value, includeINIs, parentINI);							
						}
						else
						{
							parentINI->SetValue(currentSection.c_str(), key, value);
						}
					}
				}
			}
		}
	}
	Log::note("Loading of file (name below this line) took: " + Log::getTimerValue(), Log::DEBUG);
	isLoaded = true;
}

void INIFile::SetValue(const char* section, const std::string &key, const std::string &value)
{
	if (EnsureSection(section))
	{
		getSection(section)->setValue(key, value);
	}
}

INISection* INIFile::EnsureSection(const char* section)
{
	if (auto pSection = getSection(section))
	{
		return pSection;
	}

	auto &ret = sectionList[_strdup(section)];

	ret = std::make_unique<INISection>(section);
	return ret.get();
}

INISection* INIFile::getSection(const char* section)
{
	auto it = sectionList.find(section);
	if (it != sectionList.end())
	{
		return it->second.get();
	}
	return nullptr;
}

bool INIFile::checkSectionExistance(const std::string &section)
{
	if (getSection(section) != nullptr)
	{
		return true;
	}
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

void INIFile::dumpContent()
{
	std::map<std::string, std::unique_ptr<INISection>>::iterator iter;

	//for (iter = sectionList.begin(); iter != sectionList.end(); ++iter)
	//{
//		iter->second->dumpContent();
//	}
}