#include "stdafx.h"
#include "TMPImage.hpp"
#include "../../GlobalData.hpp"
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
	_extraZDataOffset = tmpReader->readUInt();//20 bytes
	ExtraX = tmpReader->readUInt();
	ExtraY = tmpReader->readUInt();
	ExtraWidth = tmpReader->readUInt();
	ExtraHeight = tmpReader->readUInt();
	_dataPrecencyFlags = (DataPrecencyFlags) tmpReader->readUInt(); //40
	Height = tmpReader->readByte();
	TerrainType = tmpReader->readByte();
	RampType = tmpReader->readByte();
	RadarRedLeft = tmpReader->readByte();
	RadarGreenLeft = tmpReader->readByte();
	RadarBlueLeft = tmpReader->readByte();
	RadarRedRight = tmpReader->readByte();
	RadarGreenRight = tmpReader->readByte();
	RadarBlueRight = tmpReader->readByte();
	tmpReader->discardBytes(3); // discard padding 52 bytes
	TileData = tmpReader->readByteBlock(GlobalData::tileWidth * GlobalData::tileHeight / 2);
	
	//-if tileoffset+tilesize+extragraphicsize > end of file (e.g. last tile has incorrect header and thus would be bigger than the filesize) 
	//-if tileoffset + tilesize + extragraphicsize > following tile offset
	if (HasZData())
		ZData = tmpReader->readByteBlock(GlobalData::tileWidth * GlobalData::tileHeight / 2);
	if (HasExtraData() 
		&& _extraDataOffset < std::abs(ExtraWidth * ExtraHeight)
		&& offset + GlobalData::tileWidth * GlobalData::tileHeight + ExtraWidth * ExtraHeight < tmpReader->getFileSize()
		)
		ExtraData = tmpReader->readByteBlock(std::abs(ExtraWidth * ExtraHeight));
	if (HasZData() 
		&& HasExtraData() 
		&& 0 < _extraZDataOffset 
		&& _extraZDataOffset < tmpReader->getFileSize()
		&& _extraDataOffset < std::abs(ExtraWidth * ExtraHeight)
		&& offset + GlobalData::tileWidth * GlobalData::tileHeight + ExtraWidth * ExtraHeight < tmpReader->getFileSize()
		)
		ExtraZData = tmpReader->readByteBlock(std::abs(ExtraWidth * ExtraHeight));
}

bool TMPImage::HasExtraData()
{
	/* Check to see if the extra data > actual file size; if so: discard operation and ignore extra data */
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