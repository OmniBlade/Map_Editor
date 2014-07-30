#pragma once
#include <vector>

class INISection;

class IsoMapPack
{
public:
	//Trailing issues...
	#pragma pack(push, 1)
	struct IsoMapPack5Tile 
	{
		__int16 X, Y;
		__int32 TileTypeIndex;
		byte TileSubtypeIndex;
		byte Level;
		byte Unknown;
	};
	#pragma pack(pop)

	IsoMapPack(INISection* section);
	~IsoMapPack();

	/*
		Reads the encoded IsoMapPack section and decodes it
		Afterwards it puts the bytes in a unique tile
	*/
	void read();


private:
	INISection* isoPack;
	std::vector<IsoMapPack5Tile> tiles;
};

