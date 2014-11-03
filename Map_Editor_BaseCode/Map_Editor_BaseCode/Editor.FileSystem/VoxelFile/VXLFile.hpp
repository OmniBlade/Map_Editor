#pragma once
#include <string>
#include <vector>
#include <memory>

class Section;
class BinaryReader;
struct FileProperties;

class VXLFile
{
public:
	struct Header
	{
		std::string FileName;
		unsigned int PaletteCount;
		unsigned int HeaderCount;
		unsigned int TailerCount;
		unsigned int BodySize;
		byte PaletteRemapStart;
		byte PaletteRemapEnd;
	};

	VXLFile(const FileProperties& props);
	~VXLFile();

	void read();

private:
	BinaryReader* vxlReader;
	bool valid, initialized;
	Header vxlHeader;
	std::vector<std::unique_ptr<Section>> sections;

};

