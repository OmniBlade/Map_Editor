#include "stdafx.h"
#include "Speech.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"

/* static */ WWList<Speech> Speech::Array;

Speech::Speech(const std::string& id)
:ID(id)
{

}

void Speech::load(INIFile* file)
{
	INISection* section = file->getSection(ID);
	 
	if (!section)
	{
		return;
	}
	
	section->readStringValue("Text", text);
	Name = text;
	valid = true;

}