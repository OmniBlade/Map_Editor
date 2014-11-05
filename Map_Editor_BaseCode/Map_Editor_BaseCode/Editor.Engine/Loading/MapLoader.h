#pragma once
#include <memory>
#include "WWLoader.hpp"
#include "MapObjectLoader.hpp"

class INIFile;

/*
	Loads and parses the map completely with Rules INI and GameMode INI
	The map pointer is ALWAYS assumed to be an object that is destroyed outside this class (hence no deletion and simple ptr usage)
	The ptr usually is a unique_ptr
*/
class MapLoader
{
public:
	MapLoader(INIFile* map, bool keepAsOriginal = false);
	MapLoader();
	~MapLoader();

	void clearData();
	void clearOriginalMap();

	void preparseBasic();
	void load();
	void reload();
	
	void restoreMapNames(INIFile* namesFile);

	INIFile* getGameModeFromData();

private:
	static std::unique_ptr<INIFile> originalMap;
	static bool dirty;
	bool cleaned = false;
	INIFile* map;
	WWLoader wwLoader;
	MapObjectLoader objectLoader;
};

