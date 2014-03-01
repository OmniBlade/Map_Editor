#include "stdafx.h"
#include "PaletteFile.hpp"
#include <iostream>

PaletteFile::PaletteFile(const std::string& _paletteName, const std::string& _fullFileName)
:paletteName(_paletteName), fullFileName(_fullFileName)
{
	paletteReader = new BinaryReader(_fullFileName);
	readPalette();
}

PaletteFile::PaletteFile(const std::string& _paletteName, BinaryReader* _paletteReader, __int32 _offset)
:paletteName(_paletteName), paletteReader(_paletteReader), offset(_offset)
{
	paletteReader->setOffset(offset);
	readPalette();
}

void PaletteFile::readPalette()
{
	paletteBytes.reserve(256);
	for (unsigned int i = 0; i < 256; ++i)
	{
		std::cout << "===== Byte #" << i + 1 << " =====" << std::endl;

		auto redByte = paletteReader->readByte(); 
		byte red = (redByte << 2) | (redByte >> 4);

		auto greenByte = paletteReader->readByte();
		byte green = (greenByte << 2) | (greenByte >> 4);

		auto blueByte = paletteReader->readByte();
		byte blue = (blueByte << 2) | (blueByte >> 4);

		unsigned int colorByte = (unsigned int)((255 << 24) | (blue << 16) | (green << 8) | red);
		paletteBytes.push_back(colorByte);
	}
}