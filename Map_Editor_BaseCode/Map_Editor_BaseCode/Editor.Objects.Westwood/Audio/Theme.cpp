#include "stdafx.h"
#include "Theme.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/CSFManager.hpp"

/* static */ List<Theme> Theme::Array;

Theme::Theme(const std::string& id)
:ID(id)
{

}

void Theme::load(INIFile* file)
{
	INISection* section = file->getSection(ID);

	if (!section)
	{
		return;
	}

	name = CSFManager::getManager()->getValue(section->getValue("Name"));
	valid = true;
}
