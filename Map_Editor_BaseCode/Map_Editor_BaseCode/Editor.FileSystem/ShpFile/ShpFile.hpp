#pragma once

#include "ShpImage.hpp"
#include <vector>
#include <memory>

class BinaryReader;
struct FileProperties;

class ShpFile
{
public:
	ShpFile();
	ShpFile(const FileProperties& props);
	 
	~ShpFile();

	void readHeader();
	void readImages();
	ShpImage* get(int index);

	short zero;
	short width;
	short height;
	unsigned short imageCount;

private:
	int fileSize;
	BinaryReader* shpReader;
	std::vector<std::unique_ptr<ShpImage>> images;
};

