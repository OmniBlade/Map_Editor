#include "stdafx.h"
#include "IQ.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"

IQ::IQ()
{
}

void IQ::loadRules(INIFile* file)
{
	INISection* rulesSection = file->getSection("IQ");

	if (!rulesSection) return;
	
	rulesSection->readIntValue("MaxIQLevels", MaxIQLevels);
}
