#include "stdafx.h"
#include "Sound.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"

/* static */ List<Sound> Sound::Array;

Sound::Sound(const std::string& id)
:ID(id)
{

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