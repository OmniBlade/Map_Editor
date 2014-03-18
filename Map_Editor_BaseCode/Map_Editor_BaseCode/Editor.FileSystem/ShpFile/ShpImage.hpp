#pragma once

#include "../FileManager/BinaryReader.hpp"
#include <vector>

class ShpImage
{
public:
	ShpImage();
	ShpImage(BinaryReader* _shpReader, int _frameIndex);
	~ShpImage();

	void readHeader();
	void readImage();

	short x;
	short y;
	short width;
	short height;
	byte compressionType;
	byte unknown1;
	byte unknown2;
	byte unknown3;
	int unknown4;
	int zero;
	int dataOffset;
	std::vector<byte> imageData;
	int frameIndex;

private:
	BinaryReader* shpReader;
};

