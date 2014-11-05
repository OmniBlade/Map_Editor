#include "stdafx.h"
#include "MapLoader.h"
#include "..\Basics\Basic.hpp"
#include "..\Basics\Ranking.h"
#include "..\Basics\Lighting.hpp"
#include "..\Basics\SpecialFlag.hpp"
#include "..\Basics\MapStats.hpp"
#include "..\Map\Map.hpp"
#include "..\Map\Packs\IsoMapPack.hpp"
#include "..\Map\Packs\OverlayPack.hpp"
#include "..\Map\Packs\PreviewPack.h"
#include "../Game/GameModeCollection.hpp"
#include "..\..\Editor.FileSystem\MapFile\Modifications\MapMods.h"
#include "..\..\Editor.FileSystem\MapFile\Flushing\NameFlusherClass.h"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "..\..\Editor.FileSystem\IniFile\INIFile.hpp"
#include "..\..\Editor.FileSystem\IniFile\DigestClass.h"
#include "../../Config.hpp"
#include "../../Log.hpp"

/* static */ std::unique_ptr<INIFile> MapLoader::originalMap;
/* static */ bool MapLoader::dirty = false;

MapLoader::MapLoader(INIFile* map, bool keepAsOriginal /* = false */)
	:map(map)
{
	if (keepAsOriginal)
	{
		originalMap = std::make_unique<INIFile>(*map);
	}
	Log::line("Creating MapLoader instance with map, all functions be used!", Log::DEBUG);
}

MapLoader::MapLoader()
{
	Log::line("Creating MapLoader instance without map, map specific functions cannot be used!", Log::DEBUG);
}

MapLoader::~MapLoader()
{

}

void MapLoader::clearData()
{
	Log::line("Clearing all parsed data!", Log::DEBUG);
	IsoMapPack::instance()->clear();
	OverlayPack::instance()->clear();
	PreviewPack::instance()->clear();

	wwLoader.clearAll();
	objectLoader.clearAll();

	dirty = false;
}

void MapLoader::clearOriginalMap()
{
	originalMap.release();
}

void MapLoader::preparseBasic()
{
	Basic::getBasic()->parse(map);
}

void MapLoader::load()
{
	if (dirty) clearData();

	map->setDeletableState(true);
	Basic::getBasic()->parse(map); //Just to be sure, preparse
	auto rules = INIManager::instance()->get(Config::rules);
	auto mode = getGameModeFromData();

	wwLoader.loadMainRulesSections();
	wwLoader.load(rules, "Rules");
	wwLoader.load(mode, "Gamemode");
	wwLoader.setGlobalCountries();
	wwLoader.load(map, "Map");
	wwLoader.loadGlobalVariable();
	wwLoader.loadAI();

	objectLoader.load(mode, "Gamemode");
	objectLoader.setGlobalValues();
	objectLoader.load(map, "Map");

	IsoMapPack::instance()->read(map);
	OverlayPack::instance()->read(map);
	OverlayPack::instance()->createOverlayFromData();
	PreviewPack::instance()->read(map);
	Ranking::instance()->parse(map);
	MapStats::instance()->parse(map);
	SpecialFlag::instance()->parse(map);
	Lighting::instance()->parse(map);
	MapMods::instance()->parse(map);
	Basic::getBasic()->assignPointers();
	Map::instance()->setupCells();

	dirty = true;
}

void MapLoader::reload()
{
	clearData();
	map = new INIFile(*originalMap.get());
	load();
}

void MapLoader::restoreMapNames(INIFile* namesFile)
{
	if (namesFile && Basic::getBasic()->NamesFlushed)
	{
		Log::line("Restoring names to types...", Log::DEBUG);
		INIFile readNamesFile(*namesFile);
		DigestClass::validateDigest(&readNamesFile, Config::mapName + Config::namesName);
		NameFlusherClass::readAndRestoreFrom(readNamesFile);
	}
	else if (!namesFile && Basic::getBasic()->NamesFlushed)
	{
		Log::line("Digest indicates that the map has names flushed.", Log::DEBUG);
		Log::line("Unable to do so! Does '" + Config::mapName + Config::namesName + "' exist?", Log::DEBUG);
	}
}

INIFile* MapLoader::getGameModeFromData()
{
	auto basic = Basic::getBasic();
	auto modes = GameModeCollection::getInstance();

	if (basic->isSP())
	{
		return nullptr;
	}
	else if (auto mode = modes->getCurrent())
	{
		return INIManager::instance()->get(mode->fileName);
	}

	if (basic->GameModes.size() == 1)
	{
		modes->setCurrent(basic->GameModes.front());
	}
	else if (!basic->GameModes.size())
	{
		Log::line("This multiplayer map has no valid GameMode value set! Assuming game's default.", Log::DEBUG);
		modes->setCurrent(modes->standardDefault);
	}
	else
	{
		for (const auto& it : basic->GameModes)
		{
			if (!modes->isStandardDefault(it))
			{
				modes->setCurrent(it);
				Log::line("Multiple GameMode entries found, setting '" + it + "' as current GameMode.", Log::DEBUG);
				break;
			}
		}
	}

	return INIManager::instance()->get(GameModeCollection::getInstance()->getCurrent()->fileName);
}