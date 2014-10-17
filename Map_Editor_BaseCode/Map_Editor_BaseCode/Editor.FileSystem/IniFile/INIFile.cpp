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
#include "../FileManager/FileWriter.h"
#include "../FileManager/FileSystem.hpp"
#include "../FileManager/BinaryReader.hpp"
#include "../FileManager/TextReader.h"
#include "../FileManager/Managers/INIManager.hpp"
#include "../../Log.hpp"
#include "DigestClass.h"

INIFile::INIFile()
{

}

INIFile::INIFile(const FileProperties& props)
{
	load(this, props);
}

INIFile::INIFile(const FileProperties& props, INIFile* parentINI)
{
	load(parentINI, props);
}


INIFile::INIFile(const std::vector<char>& bytes)
{
	FileProperties props;

	load(this, props, &bytes);
}


void INIFile::load(INIFile* parentINI, const FileProperties& props, const std::vector<char>* bytes /* = nullptr */)
{
	TextReader* iniReader;
	if (bytes)
	{
		iniReader = new TextReader(*bytes);
	}
	else
	{
		iniReader = new TextReader(props);
	}
	
	std::string currentSection;
	std::string line;

	//Log::timerStart();

	while (!iniReader->checkEOF())
	{
		line = iniReader->readTextLine();
	
		auto comment = line.find_first_of(";");
		if (comment != std::string::npos)
		{
			line = line.substr(0, comment);
		}
		/*auto commentC = line.find_first_of("//");
		if (commentC != std::string::npos)
		{
			line = line.substr(0, commentC);
		}*/
		if (line.length())
		{
			line = StringHelper::trim(line);
			//std::cout << "Line: " << line << std::endl;
			if (line.front() == '[' && line.find_first_of("]") != std::string::npos)
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
							INIManager::instance()->loadIncludeINI(value, includeINIs, parentINI);							
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
	//Log::line("Loading of file (name below this line) took: " + Log::getTimerValue(), Log::DEBUG);
	isLoaded = true;
	
	delete iniReader;
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
	sections.push_back(section);
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
	if (getSection(section))
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

void INIFile::deleteSection(const char* section)
{
	auto it_map = sectionList.find(section);
	auto it_vector = std::find(sections.begin(), sections.end(), section);
	//auto it = std::find(sectionList.begin(), sectionList.end(), section);
	sectionList.erase(it_map);
	sections.erase(it_vector);
}

void INIFile::writeToFile(const std::string& fullPath, bool withDigest /* = false */, bool alphabeticOrder /* = true */)
{
	FileWriter iniWriter(fullPath);

	writeStartingComments(&iniWriter);

	if (alphabeticOrder)
	{
		writeAlphabetic(&iniWriter);
	}
	else
	{
		writeVectorOrder(&iniWriter);
	}

	if (withDigest)
	{
		writeDigest(&iniWriter);
	}

	iniWriter.close();
}

void INIFile::writeStartingComments(FileWriter* file)
{
	for (auto& it : comments)
	{
		if (it.empty())
		{
			file->writeBuffer("\n", 1);
		}
		else
		{
			std::string line = "; " + it + "\n";
			file->writeBuffer(line.c_str(), line.size());
		}
	}
}

void INIFile::writeAlphabetic(FileWriter* file)
{
	for (const auto& it : sectionList)
	{
		INISection* section = it.second.get();
		std::string sectionName = "\n[" + section->getSectionName() + "]\n";
		file->writeBuffer(sectionName.c_str(), sectionName.size());

		//Write A Key-Value pair
		for (unsigned int i = 0; i < section->size(); ++i)
		{
			std::string keyvalue = section->getKeyValue(i);
			file->writeBuffer(keyvalue.c_str(), keyvalue.size());
		}

		file->flush();
	}
}

void INIFile::writeVectorOrder(FileWriter* file)
{
	for (const auto& it : sections)
	{
		INISection* section = getSection(it);
		std::string sectionName = "\n[" + section->getSectionName() + "]\n";
		file->writeBuffer(sectionName.c_str(), sectionName.size());

		//Write A Key-Value pair
		for (unsigned int i = 0; i < section->size(); ++i)
		{
			std::string keyvalue = section->getKeyValue(i);
			file->writeBuffer(keyvalue.c_str(), keyvalue.size());
		}

		file->flush();
	}
}

void INIFile::writeDigest(FileWriter* file)
{
	std::string sectionName = "\n[Digest]\n";
	std::string digestValue = "1=" + DigestClass::getRandomDigest();

	file->writeBuffer(sectionName.c_str(), sectionName.size());
	file->writeBuffer(digestValue.c_str(), digestValue.size());
}