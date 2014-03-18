#pragma once

#include <string>
#include <vector>
#include "../../Editor.FileSystem/INIFile/INIFile.hpp"
#include "../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include "TheaterCollection.hpp"
class Map
{
public:
	Map(INIManager* _iniHandler, TheaterCollection* _theaterColl);
	~Map();

	void loadTheater(const std::string& _theaterName);
	//void load

private:
	INIManager* iniHandler;
	TheaterCollection* theaterColl;
	//Theater* currentTheater = nullptr;
};

