#include "stdafx.h"
#include "ShpImage.hpp"
#include "../FileManager/BinaryReader.hpp"
#include <iostream>

ShpImage::ShpImage()
{
}

ShpImage::ShpImage(BinaryReader* _shpReader, int _frameIndex)
:shpReader(_shpReader), frameIndex(_frameIndex)
{
	readHeader();
}

ShpImage::~ShpImage()
{
}

void ShpImage::readHeader()
{
	x = shpReader->readShort();
	y = shpReader->readShort();
	width = shpReader->readShort();
	height = shpReader->readShort();
	compressionType = shpReader->readByte();

	unknown1 = shpReader->readByte();
	unknown2 = shpReader->readByte();
	unknown3 = shpReader->readByte();
	unknown4 = shpReader->readInt();
	zero = shpReader->readInt();
	dataOffset = shpReader->readInt();
}

void ShpImage::readImage()
{

}