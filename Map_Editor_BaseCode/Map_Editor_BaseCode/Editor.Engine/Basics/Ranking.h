#pragma once
#include <string>

class INIFile;

class Ranking
{
public:
	static Ranking* instance();
	static void writeToINI(INIFile& file);

	void parse(INIFile* file);

private:
	static Ranking* pInstance;
	Ranking();

	std::string ParTimeEasy, ParTimeMedium, ParTimeHard;
	std::string UnderParTitle, UnderParMessage;
	std::string OverParTitle, OverParMessage;
};

