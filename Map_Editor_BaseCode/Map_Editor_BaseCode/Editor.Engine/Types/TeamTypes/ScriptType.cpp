#include "stdafx.h"
#include "ScriptType.hpp"
#include "../../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Log.hpp"

/* static */ MapObjectList<ScriptType> ScriptType::Array;

ScriptType::ScriptType(const std::string& id)
:ID(id)
{

}

void ScriptType::parse(INIFile* file, bool isGlobal_)
{
	INISection* section = file->getSection(ID);

	if (!section)
	{
		return;
	}
	
	isGlobal = isGlobal_;
	section->readStringValue("Name", Name);

	//If anyone ever resizes the limit for this...
	unsigned int scriptActionLimit = 50;
	//actionList.reserve(scriptActionLimit);
	//actionList.resize(scriptActionLimit);

	for (unsigned int i = 0; i < scriptActionLimit; ++i)
	{

		if (!section->checkKeyExistance(Log::toString(i)))
		{
			break; // Stop reading when an index is missing
		}
		else
		{
			LineSplitter parts(section->getValue(Log::toString(i)));
			if (auto sub = ScriptAction::parse(parts))
			{
				actionList.push_back(sub);
			}
			else
			{
				Log::line("Unable to parse Script Action with ID '" + ID + "'.", Log::DEBUG);
			}
		}
	}
}

void ScriptType::writeToINI(INIFile& file)
{
	std::stringstream number;
	int i = 0;
	for (auto& it : Array.objectTypeList)
	{
		if (!it->isGlobal)
		{
			number << i;
			file.SetValue("ScriptTypes", number.str(), it->ID);
			++i;
			number.str(std::string());
			it->writeContentToINI(file);
		}
	}
}

void ScriptType::writeContentToINI(INIFile& file)
{
	file.SetValue(ID.c_str(), "Name", Name);
	std::stringstream number;
	int i = 0;
	for (auto& it : this->actionList)
	{
		number << i;
		file.SetValue(ID.c_str(), number.str(), it->asString());	
		++i;
		number.str(std::string());

		if (i == 50) //Only write 0 - 49!
			break;
	}
}