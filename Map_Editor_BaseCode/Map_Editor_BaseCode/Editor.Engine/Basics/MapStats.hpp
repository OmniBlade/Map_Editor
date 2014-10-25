#pragma once
#include <string>
#include <memory>

class Theater;
class INIFile;
class TheaterDefinition;

class MapStats
{
public:
	struct SizeStruct
	{
		int Left;
		int Top;
		int Width;
		int Height;
	};

	static MapStats* instance();
	static void writeToINI(INIFile& file);

	void parse(INIFile* map); 
	std::string sizeAsString(SizeStruct it);

	const std::string WATER = "Water", CLEAR = "Clear";
	std::string TheaterStr, Fill, SizeStr, LocalSizeStr;
	SizeStruct Size;
	SizeStruct LocalSize;

	TheaterDefinition* pTheaterDef;
	std::unique_ptr<Theater> pTheater;

private:
	static MapStats* it;
	MapStats();
};

