#pragma once

#include "../HvaFile/HVAFile.hpp"

class BinaryReader;
struct FileProperties;

class VXLFile
{
public:
	VXLFile(const FileProperties& props);
	~VXLFile();

private:
	BinaryReader* vxlReader;
	HVAFile* hvaFile;

};

