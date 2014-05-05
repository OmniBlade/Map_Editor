#pragma once

class BinaryReader;

struct FileProperties;

class HVAFile
{
public:
	HVAFile(const FileProperties& props);
	~HVAFile();

private:
	BinaryReader* hvaReader;
};

