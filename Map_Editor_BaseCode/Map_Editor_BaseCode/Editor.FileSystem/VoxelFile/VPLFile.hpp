#pragma once

#include <vector>

class BinaryReader;
struct FileProperties;

class VPLFile
{
public:
	static VPLFile* getVPL();
	void setProperties(const FileProperties& props);
	~VPLFile();

	void read();

	unsigned int firstRemap;
	unsigned int lastRemap;
	unsigned int numSections;
	unsigned int unknown;

	std::vector<std::vector<byte>> lookupSections;
	byte getPaletteIndex(byte normal, byte maxNomal, byte color);

private:
	VPLFile();
	static VPLFile* vplFile;
	BinaryReader* vplReader;
};

