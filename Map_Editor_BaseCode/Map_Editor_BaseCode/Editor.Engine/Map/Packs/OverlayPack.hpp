#pragma once
#include <string>
#include <vector>

class INIFile;
class PackType;

class OverlayPack
{
public:
	OverlayPack(INIFile* file);
	~OverlayPack();

	static void writeToINI(INIFile& file);
	static OverlayPack* instance;

	void read(INIFile* map);
	void write();
	void createOverlayFromData();
	void writeContentToINI(INIFile& file, PackType* pack, const std::string& sectionName);

	std::vector<byte> prepareDataForWriting(byte defaultByte, bool useIndex);

private:
	bool useOverlay = true;
	PackType* pOverlayPack;
	PackType* pOverlayDataPack;
	INIFile* file;
	const static int F80_MAX = 262144;
};

