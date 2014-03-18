#pragma once
#include "../FileManager/BinaryReader.hpp"

struct FileProperties;

class HVAFile
{
public:
	HVAFile(const FileProperties& props);
	~HVAFile();

private:
	BinaryReader* hvaReader;
};

