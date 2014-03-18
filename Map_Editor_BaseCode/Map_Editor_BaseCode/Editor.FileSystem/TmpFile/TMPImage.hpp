#pragma once

#include "../FileManager/BinaryReader.hpp"

class TMPImage
{
public:
	TMPImage(BinaryReader* _tmpReader, int offset = 0);
	void readImage();
	bool HasExtraData();
	bool HasZData();
	bool HasDamagedData(); //Should only be applicable for BRIDGES

	// header stuff
	int X;
	int Y;

	int ExtraX;
	int ExtraY;
	int ExtraWidth;
	int ExtraHeight;
	byte Height;
	byte TerrainType;
	byte RampType;
	byte RadarRedLeft;
	byte RadarGreenLeft;
	byte RadarBlueLeft;
	byte RadarRedRight;
	byte RadarGreenRight;
	byte RadarBlueRight;

	std::vector<byte> TileData; // always available
	std::vector<byte> ExtraData; // available is presency flags says so
	std::vector<byte> ZData; // available is presency flags says so
	std::vector<byte> ExtraZData; // available is presency flags says so

private:
	BinaryReader* tmpReader;

	enum DataPrecencyFlags : unsigned int
	{
		enumExtraData = 0x01,
		enumZData = 0x02,
		enumDamagedData = 0x04,
	};

	int _extraDataOffset;
	int _zDataOffset;
	int _extraZDataOffset;
	int offset;

	DataPrecencyFlags _dataPrecencyFlags;
};

