/*
 * INIFile.cpp
 *
 *  Created on: 27 nov. 2013
 *      Author: Rik
 *	  Semester: CAR
 */

#include "stdafx.h"
#include "CStringHelper.hpp"
#include "DigestClass.h"
#include "../../Config.hpp"
#include "../FileManager/FileWriter.h"
#include "../FileManager/FileSystem.hpp"
#include "../FileManager/BinaryReader.hpp"
#include "../FileManager/TextReader.h"
#include "../FileManager/Managers/INIManager.hpp"
#include "../../Log.hpp"

INIFile::INIFile()
{

}

INIFile::INIFile(const INIFile& other)
	:isLoaded(other.isLoaded), canDeleteFrom(other.canDeleteFrom), path(other.path), 
	digest(other.digest), includeINIs(other.includeINIs), sections(other.sections),
	comments(other.comments)
{
	for (const auto& it : other.sectionList)
	{
		sectionList[ItemKey(it.first.get(), true)] = std::make_unique<INISection>(*it.second);
	}
}

INIFile::INIFile(const FileProperties& props)
{
	this->path = props.path;
	load(this, props);
}

INIFile::INIFile(const FileProperties& props, INIFile* parentINI)
{
	this->path = props.path;
	load(parentINI, props);
}

INIFile::INIFile(const FileProperties& props, TextReader* reader)
{
	load(this, props, reader);
}


void INIFile::load(INIFile* parentINI, const FileProperties& props, TextReader* reader /* = nullptr */)
{
	TextReader* iniReader;

	reader != nullptr ? iniReader = reader : iniReader = new TextReader(props);
	
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

	setupDigest();
}

void INIFile::SetValue(const char* section, std::string key, const std::string value, bool insertAtFront /* = false */)
{
	if (EnsureSection(section, insertAtFront))
	{
		getSection(section)->setValue(key, value);
	}
}

INISection* INIFile::EnsureSection(const char* section, bool insertAtFront /* = false */)
{
	if (auto pSection = getSection(section))
	{
		return pSection;
	}

	auto &ret = sectionList[ItemKey(section, true)];

	ret = std::make_unique<INISection>(section);

	if (std::find(sections.begin(), sections.end(), section) == sections.end())
	{
		if (insertAtFront)
		{
			sections.insert(sections.begin(), section);
		}
		else
		{
			sections.push_back(section);
		}
	}

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

bool INIFile::sectionExists(const std::string &section)
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

void INIFile::dumpContent()
{
	for (const auto& it : sections)
	{
		getSection(it.c_str())->dumpContent();
	}
}

int INIFile::generateAndGetCheckSum(int type /* = -1 */)
{
	/* Type */
	// -1 - nothing
	// 0 - keys
	// 1 - values

	int checksum = 0;

	if (type == 0)
	{
		for (const auto& it : sections)
		{
			if (strcmp(it.c_str(), "Digest") != 0)
				checksum += getSection(it)->checkSumKeys();
		}
	}
	else if (type == 1)
	{
		for (const auto& it : sections)
		{
			if (strcmp(it.c_str(), "Digest") != 0)
				checksum += getSection(it)->checkSumValues();
		}
	}
	else
	{
		return checksum;
	}
	
	return checksum;
}

void INIFile::copyINITo(INIFile* file)
{
	if (!file) return;

	for (const auto& it : sections)
	{
		auto section = getSection(it);
		file->addSectionByCopy(section);
	}
}

void INIFile::copyFromINI(INIFile* file)
{
	if (!file) return;

	for (const auto& it : file->getSectionList())
	{
		addSectionByCopy(file->getSection(it));
	}
}

void INIFile::addSectionByCopyAfter(const std::string& name, INISection* section)
{
	if (name.empty())
	{
		return;
	}

	auto iter_name = std::find(sections.begin(), sections.end(), name);
	if (iter_name != sections.end())
	{
		if (std::find(sections.begin(), sections.end(), section->getSectionName()) == sections.end())
			sections.insert((iter_name + 1), section->getSectionName());
	}
	else
	{
		if (std::find(sections.begin(), sections.end(), section->getSectionName()) == sections.end())
			sections.insert(sections.begin(), section->getSectionName());
	}
	addSectionByCopy(section);
}

void INIFile::clearAll(bool confirmation)
{
	if (confirmation)
	{
		sections.clear();
		sectionList.clear();
	}
}

void INIFile::deleteSection(const char* section)
{
	auto it_map = sectionList.find(section);
	auto it_vector = std::find(sections.begin(), sections.end(), section);
	
	if (it_map != sectionList.end())
		sectionList.erase(it_map);
	if (it_vector != sections.end())
		sections.erase(it_vector);
}

void INIFile::writeToSameFile(bool alphabetic)
{
	if (!isLoaded || path.empty())
	{
		Log::line(L"Path for INI to write does not exist, unable to write!", Log::DEBUG);
	}
	else
	{
		writeToFile(path, alphabetic);
	}
}

void INIFile::writeToFile(const std::string& fullPath, bool alphabeticOrder /* = false */)
{
	FileWriter iniWriter(fullPath);

	if (path.empty())
		path = std::move(fullPath);

	writeStartingComments(&iniWriter);

	if (generatesOwnDigest)
		setDigestForWriting(cannotWriteTo);
	
	alphabeticOrder ? writeAlphabetic(&iniWriter) : writeVectorOrder(&iniWriter);
	
	std::string eof = "\n;eof";
	iniWriter.writeBuffer(eof.c_str(), eof.size());

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

void INIFile::setDigestForWriting(bool writeLock /* = false */)
{
	DigestClass::clearChecksumIntegers();
	digest = DigestClass::getCustomDigestFor(this, writeLock);
	SetValue("Digest", "1", digest);

	Log::line("Generated Digest: " + digest + " | Write lock: " + Log::toString(writeLock), Log::DEBUG);
}

void INIFile::setupDigest()
{
	INISection* pSection = getSection("Digest");
	if (pSection)
	{
		setDigest(pSection->getValue(pSection->getKey(0)));
		//deleteSection("Digest");
	}
}