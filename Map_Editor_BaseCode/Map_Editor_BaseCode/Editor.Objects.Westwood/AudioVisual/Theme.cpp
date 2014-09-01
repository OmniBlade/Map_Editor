#include "stdafx.h"
#include "Theme.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/CSFManager.hpp"

/* static */ WWList<Theme> Theme::Array;

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

	Name = section->getValue("Name");
	WUIName = CSFManager::getManager()->getValue(Name);
	
	valid = true;
}
