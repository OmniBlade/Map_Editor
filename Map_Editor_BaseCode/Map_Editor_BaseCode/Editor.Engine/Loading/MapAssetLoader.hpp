#pragma once

#include "../../Editor.FileSystem/IniFile/INIFile.hpp"

class MapAssetLoader
{
public:
	MapAssetLoader();

	void load(INIFile* mapFile);

	/*
		This function is used to load sections like TeamTypes, TaskForces, ScriptTypes and Houses
		These sections use a FOA-ish way to get loaded (like with BuildingTypes and friends)
	*/
	void allocateMainData(INIFile* mapFile);
	
	void loadAll(INIFile* mapFile);

};

