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
