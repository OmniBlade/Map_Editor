#pragma once

#include "../FileManager/BinaryReader.hpp"
#include <vector>
#include <string>

struct FileProperties;

class PaletteFile
{
public:
	PaletteFile(const FileProperties& props);

	void readPalette();

private:
	BinaryReader* paletteReader;
	std::vector<unsigned int> paletteBytes;

};
