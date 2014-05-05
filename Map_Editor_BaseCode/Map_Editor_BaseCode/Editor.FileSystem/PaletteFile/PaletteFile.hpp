#pragma once

#include <vector>
#include <string>

class BinaryReader;
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
