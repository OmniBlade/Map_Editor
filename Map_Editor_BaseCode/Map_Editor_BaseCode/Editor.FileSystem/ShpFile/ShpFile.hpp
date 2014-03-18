#pragma once

#include "ShpImage.hpp"
#include <vector>
#include <memory>
#include "../FileManager/BinaryReader.hpp"
//#include "../FileManager/FileSystem.hpp"

struct FileProperties;

class ShpFile
{
public:
	ShpFile();
	ShpFile(const FileProperties& props);
	 
	~ShpFile();

	void readHeader();
	void readImages();

	short zero;
	short width;
	short height;
	unsigned short imageCount;

private:
	int fileSize;
	BinaryReader* shpReader;
	std::vector<std::unique_ptr<ShpImage>> images;
};

