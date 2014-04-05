#pragma once

#include "../FileManager/BinaryReader.hpp"
#include "TMPImage.hpp"
#include <string>
#include <vector>
#include <memory>

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

