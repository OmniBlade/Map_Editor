#include "stdafx.h"
#include "ScriptType.hpp"
#include "../../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../../Log.hpp"

/* static */ ObjectList<ScriptType> ScriptType::Array;

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

	for (unsigned int i = 0; i < 50; ++i)
	{

		if (!section->checkKeyExistance(Log::toString(i)))
			break; // Stop reading when an index is missing

	}

}
