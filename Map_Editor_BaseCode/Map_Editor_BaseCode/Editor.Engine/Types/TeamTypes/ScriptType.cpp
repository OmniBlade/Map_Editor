#include "stdafx.h"
#include "ScriptType.hpp"
#include "../../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../../Log.hpp"

ScriptType::ScriptType(const std::string& id)
:ID(id)
{

}

void ScriptType::parse(INIFile* file)
{
	INISection* section = file->getSection(ID);

	section->readStringValue("Name", Name);

	Log::note("Types of ScriptType aren't parsed yet!");
	for (unsigned int i = 0; i < 50; ++i)
	{

		if (!section->checkKeyExistance(Log::toString(i)))
			break; // Stop reading when an index is missing

	}

}
