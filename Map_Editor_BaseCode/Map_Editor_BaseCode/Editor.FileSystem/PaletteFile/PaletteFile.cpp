#include "stdafx.h"
#include "PaletteFile.hpp"
#include "../FileManager/FileSystem.hpp"
#include <iostream>

PaletteFile::PaletteFile(const FileProperties& props)
:paletteReader(props.reader)
{
	paletteReader->setOffset(props.offset);
	paletteReader->setSize(props.size);
	readPalette();
}

void PaletteFile::readPalette()
{
	paletteBytes.reserve(256);
	for (unsigned int i = 0; i < 256; ++i)
	{
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