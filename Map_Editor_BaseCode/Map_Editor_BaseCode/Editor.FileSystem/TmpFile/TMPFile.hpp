#pragma once

#include "TMPImage.hpp"
#include <string>
#include <vector>
#include <memory>

class BinaryReader;
struct FileProperties;

class TMPFile
{
public:
	TMPFile(const FileProperties& props);

	void readHeader();

	int width;
	int height;
	int tileWidth;
	int tileHeight;
	int amountOfFrames;

private:
	BinaryReader* tmpReader;
	std::string tmpName;

	std::vector<std::unique_ptr<TMPImage>> images;
};

