#include "stdafx.h"
#include "Ranking.h"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"

/* static */ Ranking* Ranking::pInstance;
/* static */ Ranking* Ranking::instance()
{
	if (!pInstance)
	{
		pInstance = new Ranking();
	}
	else
	{
		return pInstance;
	}
	return pInstance;
}

Ranking::Ranking()
{
}

void Ranking::writeToINI(INIFile& file)
{
	auto it = instance();

	file.SetValue("Ranking", "ParTimeEasy", it->ParTimeEasy);
	file.SetValue("Ranking", "ParTimeMedium", it->ParTimeMedium);
	file.SetValue("Ranking", "ParTimeHard", it->ParTimeHard);
	file.SetValue("Ranking", "UnderParTitle", it->UnderParTitle);
	file.SetValue("Ranking", "UnderParMessage", it->UnderParMessage);
	file.SetValue("Ranking", "OverParTitle", it->OverParTitle);
	file.SetValue("Ranking", "OverParMessage", it->OverParMessage);
}

void Ranking::parse(INIFile* file)
{
	INISection* section = file->getSection("Ranking");

	if (!section)
	{
		return;
	}

	section->readDeletableStringValue("ParTimeEasy", ParTimeEasy);
	section->readDeletableStringValue("ParTimeMedium", ParTimeMedium);
	section->readDeletableStringValue("ParTimeHard", ParTimeHard);
	section->readDeletableStringValue("UnderParTitle", UnderParTitle);
	section->readDeletableStringValue("UnderParMessage", UnderParMessage);
	section->readDeletableStringValue("OverParTitle", OverParTitle);
	section->readDeletableStringValue("OverParMessage", OverParMessage);

	if (!section->size())
	{
		file->deleteSection("Ranking");
	}
}

