#pragma once
#include "../FileManager/BinaryReader.hpp"
#include "../HvaFile/HVAFile.hpp"

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

