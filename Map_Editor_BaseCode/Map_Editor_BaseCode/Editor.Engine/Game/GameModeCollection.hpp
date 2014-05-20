#pragma once

#include <vector>
#include <memory>
#include "GameMode.hpp"

class GameModeCollection
{
public:
	~GameModeCollection();
	static GameModeCollection* getInstance();
	void parse();
	GameMode* getCurrent() { return current; };
	void setCurrent(const std::string& name);

private:
	static GameModeCollection* instance;
	GameModeCollection();

	GameMode* current;
	std::vector<std::unique_ptr<GameMode>> modes;
};

