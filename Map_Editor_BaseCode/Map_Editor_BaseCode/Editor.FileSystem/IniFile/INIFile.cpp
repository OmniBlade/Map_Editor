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

INIFile::INIFile(const std::vector<char>& file)
:enc(file)
{
	load(this);
}

void INIFile::load(INIFile* parentINI)
{
	std::string currentSection;
	std::string line;

	Log::timerStart();

	while (checkEOF() == false)
	{
		line = readTextLine();
	
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

						//Log::line("Key '" + key + "' in section '" + currentSection + "' is too long (longer than 512 characters):", Log::DEBUG);
						//Log::line("Parsed: " + corrValue, Log::EXTRA);
						//Log::line("Cut-off: " + errValue, Log::EXTRA);
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
	Log::line("Loading of file (name below this line) took: " + Log::getTimerValue(), Log::DEBUG);
	isLoaded = true;
}

void INIFile::SetValue(const char* section, std::string key, const std::string value)
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

std::string INIFile::readTextLine()
{
	if (iniReader)
		return iniReader->readTextLine();

	char line[2048];

	for (int i = 0; i < 2048; ++i)
	{
		line[i] = enc[atEnc];
		atEnc++;
		
		if (sizeof(line) > 1 && line[i - 1] == '\r' && line[i] == '\n') //This check saves an additional call to this function by INIFile
		{
			line[i - 1] = '\0';
			return line;
		}
		else if (line[i] == '\n' || line[i] == '\0')
		{
			line[i] = '\0';
			return line;
		}
	}

	bool endReached = false;
	while (endReached == false)
	{
		char currentChar = enc[atEnc];

		switch (currentChar)
		{
		case '\n':
		case EOF:
		case '\0':
		case '\r':
			endReached = true;
		}
		atEnc++;
	}
	line[2047] = '\0';
	return line;
}

bool INIFile::checkEOF()
{
	if (iniReader)
	{
		return iniReader->checkEOF();
	}
	else if (atEnc == enc.size()-1)
	{
		return true;
	}
	return false;
}

void INIFile::dumpContent()
{
	std::map<std::string, std::unique_ptr<INISection>>::iterator iter;

	//for (iter = sectionList.begin(); iter != sectionList.end(); ++iter)
	//{
//		iter->second->dumpContent();
//	}
}