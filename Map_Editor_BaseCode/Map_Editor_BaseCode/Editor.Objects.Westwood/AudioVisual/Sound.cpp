#include "stdafx.h"
#include "Sound.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"

/* static */ WWList<Sound> Sound::Array;

Sound::Sound(const std::string& id)
:ID(id)
{
	Name = ID;
}

void Sound::load(INIFile* file)
{
	INISection* section = file->getSection(ID);

	if (!section)
	{
		return;
	}
	else
	{
		valid = true;
	}
}