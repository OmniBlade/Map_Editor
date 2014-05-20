#pragma once

#include <string>

class GameMode
{
public:
	GameMode(const std::string& line);
	void parse(const std::string& line);

	std::string GUIName, STTName, fileName, iniName;
	std::wstring WGUIName, WSTTName;
	bool rmgAllowed = false;
};

