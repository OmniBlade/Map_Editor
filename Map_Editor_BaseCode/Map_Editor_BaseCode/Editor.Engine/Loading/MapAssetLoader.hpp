#pragma once

#include "../../Editor.FileSystem/IniFile/INIFile.hpp"

class MapAssetLoader
{
public:
	MapAssetLoader();

	void clearAll();

	void load(INIFile* mapFile, const std::string& name = "");

	/*
		This function is used to load sections like TeamTypes, TaskForces, ScriptTypes and Houses
		These sections use a FOA-ish way to get loaded (like with BuildingTypes and friends)
		@param mapFile The INI file that contains map 'code'
	*/
	void allocateMainData(INIFile* mapFile, const std::string& name = "");

	/*
		Loads all the content from the given INI file
		@param mapFile The INI file that contains map 'code'
	*/
	void loadAll(INIFile* mapFile, const std::string& name = "");

	/*
		Updates all Triggers that have an attached Trigger set,
		this is used because a Trigger can have any other Trigger as a child,
		if that child isn't loaded yet
	*/
	void updateTriggerChilds();

	/* 
		Dumps misc data of the parsed content, currently stuffed with counts and sizes of what exists in the map
	*/
	void dumpTypes();

	void setGlobalValues();
};

