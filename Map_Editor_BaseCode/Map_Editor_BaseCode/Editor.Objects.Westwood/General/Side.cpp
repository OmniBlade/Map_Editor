#include "stdafx.h"
#include "Side.hpp"
#include "../../Log.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"

/* static */ Side* Side::it = nullptr;
/* static */ Side* Side::instance()
{
	if (!it)
	{
		it = new Side();
	}
	else
	{
		return it;
	}
	return it;
}

Side::Side()
{

}

void Side::loadRules(INIFile* file)
{
	INISection* rulesSection = file->getSection("Sides");
	if (!rulesSection) return;

	for (const auto& it : *rulesSection)
	{
		sideKeys.push_back(it);
		sideList[it] = std::make_unique<LineSplitter>(rulesSection->getValue(it.c_str()));
	}
}

int Side::getSideIndexByCountry(const std::string& name)
{
	for (unsigned int i = 0; i < sideKeys.size(); ++i)
	{
		LineSplitter* split = sideList[sideKeys[i]].get();
		if (split->exists(name))
		{
			return i;
		}
	}
	return -1;
}

int Side::getSideIndexByName(const std::string& name)
{
	for (unsigned int i = 0; i < sideKeys.size(); ++i)
	{
		if (sideKeys[i] == name)
		{
			return i;
		}
	}
	return -1;
}

std::string Side::getSideName(const std::string& name)
{
	for (unsigned int i = 0; i < sideKeys.size(); ++i)
	{
		LineSplitter* split = sideList[sideKeys[i]].get();
		if (split->exists(name))
		{
			return sideKeys[i];
		}
	}
	return "";
}