#pragma once
#include <vector>
#include <memory>

class INISection;
class INIFile;
class PackType;

class IsoMapPack
{
public:
	static IsoMapPack* instance;
	static void writeToINI(INIFile& file);

	//Trailing issues...
	#pragma pack(push, 1)
	struct IsoMapPack5Tile 
	{//Size is 11, this is correct
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

	/*
		Write the decoded IsoMapPack section and encode it
	*/
	void write();

	PackType* getPack() { return this->pack; };

private:
	bool hasIsoData = false;
	INISection* isoPack;
	PackType* pack;
	std::vector<IsoMapPack5Tile> tiles;
};

