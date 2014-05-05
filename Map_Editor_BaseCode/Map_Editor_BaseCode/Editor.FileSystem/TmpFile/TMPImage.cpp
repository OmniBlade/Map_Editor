#include "stdafx.h"
#include "TMPImage.hpp"
#include "../../Config.hpp"
#include "../FileManager/BinaryReader.hpp"
#include <cmath>
#include <iostream>

TMPImage::TMPImage(BinaryReader* _tmpReader, int _offset)
:tmpReader(_tmpReader), offset(_offset)
{
	tmpReader->setOffset(offset);
	readImage();
}

void TMPImage::readImage()
{	
	X = tmpReader->readUInt();				
	Y = tmpReader->readUInt();
	_extraDataOffset = tmpReader->readUInt();
	_zDataOffset = tmpReader->readUInt();
	_extraZDataOffset = tmpReader->readUInt();
	ExtraX = tmpReader->readUInt();
	ExtraY = tmpReader->readUInt();
	ExtraWidth = tmpReader->readUInt();
	ExtraHeight = tmpReader->readUInt();
	_dataPrecencyFlags = (DataPrecencyFlags) tmpReader->readUInt();
	Height = tmpReader->readByte();
	TerrainType = tmpReader->readByte();
	RampType = tmpReader->readByte();
	RadarRedLeft = tmpReader->readByte();
	RadarGreenLeft = tmpReader->readByte();
	RadarBlueLeft = tmpReader->readByte();
	RadarRedRight = tmpReader->readByte();
	RadarGreenRight = tmpReader->readByte();
	RadarBlueRight = tmpReader->readByte();
	tmpReader->discardBytes(3); // discard padding
	TileData = tmpReader->readByteBlock(Config::tileWidth * Config::tileHeight / 2);

	if (HasZData())
		ZData = tmpReader->readByteBlock(Config::tileWidth * Config::tileHeight / 2);
	if (HasExtraData() 
		&& _extraDataOffset < std::abs(ExtraWidth * ExtraHeight)
		&& offset + Config::tileWidth * Config::tileHeight + ExtraWidth * ExtraHeight < tmpReader->getFileSize()
		)
		ExtraData = tmpReader->readByteBlock(std::abs(ExtraWidth * ExtraHeight)); // Crash here
	if (HasZData() 
		&& HasExtraData()
		&& 0 < _extraZDataOffset
		&& _extraZDataOffset < tmpReader->getFileSize()
		&& _extraDataOffset < std::abs(ExtraWidth * ExtraHeight)
		&& offset + Config::tileWidth * Config::tileHeight + ExtraWidth * ExtraHeight < tmpReader->getFileSize() // See if offset is greater than file size
		)
		ExtraZData = tmpReader->readByteBlock(std::abs(ExtraWidth * ExtraHeight));
}

bool TMPImage::HasExtraData()
{
	return (_dataPrecencyFlags & DataPrecencyFlags::enumExtraData) == DataPrecencyFlags::enumExtraData;
}

bool TMPImage::HasZData()
{
	return (_dataPrecencyFlags & DataPrecencyFlags::enumZData) == DataPrecencyFlags::enumZData;
}

bool TMPImage::HasDamagedData()
{
	return (_dataPrecencyFlags & DataPrecencyFlags::enumDamagedData) == DataPrecencyFlags::enumDamagedData;
}