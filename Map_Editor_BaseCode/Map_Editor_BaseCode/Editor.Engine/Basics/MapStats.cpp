#include "stdafx.h"
#include "MapStats.hpp"
#include "../Map/TheaterCollection.hpp"
#include  "../Map/TheaterDefinition.hpp"
#include "../Game/Theater.hpp"
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

void MapStats::parse()
{
	INIFile* map = INIManager::instance()->get(Config::mapName);
	INISection* section = map->getSection("Map");

	section->readStringValue("Theater", TheaterStr);
	section->readStringValue("Fill", Fill);
	section->readStringValue("Size", SizeStr);
	section->readStringValue("LocalSize", LocalSizeStr);

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