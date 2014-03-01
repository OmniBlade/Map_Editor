#pragma once

#include "../../Reading/BinaryReader.hpp"
#include <vector>
#include <string>

class PaletteFile
{
public:
	PaletteFile(const std::string& _paletteName, const std::string& _fullFileName);
	PaletteFile(const std::string& _paletteName, BinaryReader* _paletteReader, __int32 _offset);
	void readPalette();


private:
	__int32 offset = 0;
	std::string paletteName;
	std::string fullFileName;
	BinaryReader* paletteReader;
	std::vector<unsigned int> paletteBytes;

};
