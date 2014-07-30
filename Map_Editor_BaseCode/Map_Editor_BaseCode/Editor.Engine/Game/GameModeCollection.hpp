#pragma once

#include <vector>
#include <memory>
#include "GameMode.hpp"

class GameModeCollection
{
public:
	~GameModeCollection();
	static GameModeCollection* getInstance();
	
	/*
		Parses the gamemode INI file and creates a GameMode object for each found game mode
	*/
	void parse();
	
	/*
		Returns the currently used game mode
		@return current A pointer to the currently used game mode
	*/
	GameMode* getCurrent() { return current; };
	
	/*
		Sets the current gamemode to the one specified by the parameter
		@param name The INI name of the game mode (such as 'unholy' or 'cooperative')
	*/
	void setCurrent(const std::string& name);

private:
	static GameModeCollection* instance;
	GameModeCollection();

	GameMode* current;
	std::vector<std::unique_ptr<GameMode>> modes;
};

