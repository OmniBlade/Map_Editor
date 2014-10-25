#include "stdafx.h"
#include "MapStats.hpp"
#include "../Map/Theater/TheaterCollection.hpp"
#include "../Map/Theater/TheaterDefinition.hpp"
#include "../Map/Theater/Theater.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../Config.hpp"

/* static */ MapStats* MapStats::it;
/* static */ MapStats* MapStats::instance()
{
	if (it)
		return it;
	else
		it = new MapStats();
	return it;
}

MapStats::MapStats()
{
}

void MapStats::writeToINI(INIFile& file)
{
	MapStats* it = instance();
	file.SetValue("Map", "Theater", it->TheaterStr);
	file.SetValue("Map", "Size", it->sizeAsString(it->Size));
	file.SetValue("Map", "LocalSize", it->sizeAsString(it->LocalSize));
	if(!it->Fill.empty()) file.SetValue("Map", "Fill", it->Fill);
}

void MapStats::parse(INIFile* map)
{
	INISection* section = map->getSection("Map");

	section->readDeletableStringValue("Theater", TheaterStr);
	section->readDeletableStringValue("Fill", Fill);
	section->readDeletableStringValue("Size", SizeStr);
	section->readDeletableStringValue("LocalSize", LocalSizeStr);

	LineSplitter sizeSplit(SizeStr);
	sizeSplit.pop(Size.Left);
	sizeSplit.pop(Size.Top);
	sizeSplit.pop(Size.Width);
	sizeSplit.pop(Size.Height);

	LineSplitter lSizeSplit(LocalSizeStr);
	lSizeSplit.pop(LocalSize.Left);
	lSizeSplit.pop(LocalSize.Top);
	lSizeSplit.pop(LocalSize.Width);
	lSizeSplit.pop(LocalSize.Height);

	pTheaterDef = TheaterCollection::getInstance()->getByININame(TheaterStr);
	pTheater = std::make_unique<Theater>(pTheaterDef->INIFile);

	if (!section->size())
	{
		map->deleteSection("Map");
	}
}

std::string MapStats::sizeAsString(SizeStruct it)
{
	char buffer[512];
	sprintf_s(buffer, 512, "%d,%d,%d,%d",
		it.Left,
		it.Top,
		it.Width,
		it.Height
		);

	return buffer;
}