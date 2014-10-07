#pragma once
#include <string>
#include <vector>

class House;
class Theme;
class Movie;
class INIFile;

class Basic
{
public:
	
	static Basic* getBasic();
	void assignPointers();
	void parse();
	static void writeToINI(INIFile& file);
	static bool isSP();
	static bool isMP();
	static bool isCoop();

	std::string gamemodesAsString();
	std::string unitsAsString();
	std::string unitsMaxAsString();

	std::string Name, Player, Briefing, ThemeStr, Intro, Brief, Win, Lose, Action, PostScore, PreMapSelect;
	std::string NextScenario, AltNextScenario, GameModesStr, AllowableUnitsStr, AllowableMaxStr;
	
	float CarryOverMoney;
	int NewINIFormat, CarryOverCap, Percent, StartingDropShips, HomeCell, AltHomeCell, InitTime, MaxPlayer, MinPlayer;
	bool EndOfGame, SkipScore, OneTimeOnly, SkipMapSelect, Official, IgnoreGlobalAITriggers, TruckCrate, TrainCrate, CivEvac;
	bool TimerInherit, FillSilos, MultiplayerOnly, TiberiumGrowthEnabled, VeinGrowthEnabled, IceGrowthEnabled, TibDeathToVisc, FreeRadar;

	std::vector<std::string> GameModes;
	std::vector<std::string> AllowableUnits;
	std::vector<int> AllowableUnitsMaximums;

	House* pPlayer;
	Theme* pTheme;
	Movie* pBriefing;
	Movie* pIntro;
	Movie* pBrief;
	Movie* pWin;
	Movie* pLose;
	Movie* pAction;
	Movie* pPostScore;

private:
	static Basic* instance;
	Basic();

	bool isACoop = false;
};

