#pragma once

#include <string>

class GameMode
{
public:
	GameMode(const std::string& line);
	
	/*
		Parses the GameMode specified in the parameter
		@param line The line which contains the gamemode information
	*/
	void parse(const std::string& line);

	std::string GUIName, STTName, fileName, iniName;
	std::wstring WGUIName, WSTTName;
	bool rmgAllowed = false;
};

