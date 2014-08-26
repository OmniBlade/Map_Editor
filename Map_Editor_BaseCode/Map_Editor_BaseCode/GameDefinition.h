#pragma once
/*
	The type of game that is used
	Either the Base game (TS / RA2) or an Expansion pack (FS / YR)!
	Hardcoding to RA2/YR or TS/FS is done in the ConfigFile class, ConfigLoader only checks if the game is not set to Undefined
*/
class Game
{
public:
	enum class Type
	{
		Base = 0,
		Expansion = 1,
		Undefined = 2,
	};
	static Type title;

};
