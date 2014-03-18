#include "stdafx.h"
#include "TMPImage.hpp"
#include "../../GlobalData.hpp"
#include <cmath>
#include <iostream>

TMPImage::TMPImage(BinaryReader* _tmpReader, int _offset)
:tmpReader(_tmpReader), offset(_offset)
{
	readImage();
}

void TMPImage::readImage()
{
	tmpReader->setOffset(offset);
	
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
	RadarGreenLeft = tmpReader->readByte(); ;
	RadarBlueLeft = tmpReader->readByte(); ;
	RadarRedRight = tmpReader->readByte(); ;
	RadarGreenRight = tmpReader->readByte(); ;
	RadarBlueRight = tmpReader->readByte(); ;
	tmpReader->discardBytes(3); // discard padding
	TileData = tmpReader->readByteBlock(GlobalData::tileWidth * GlobalData::tileHeight / 2);
	
	if (HasZData())
		ZData = tmpReader->readByteBlock(GlobalData::tileWidth * GlobalData::tileHeight / 2);
	if (HasExtraData())
		ExtraData = tmpReader->readByteBlock(std::abs(ExtraWidth * ExtraHeight));
	if (HasZData() && HasExtraData() && 0 < _extraZDataOffset && _extraZDataOffset < tmpReader->getFileSize())
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