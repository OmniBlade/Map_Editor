#pragma once
#include <string>
#include <vector>
#include <memory>

class INIFile;
class PackType;

class OverlayPack
{
public:
	static OverlayPack* instance();
	static void writeToINI(INIFile& file);

	void clear()
	{
		pOverlayDataPack.release();
		pOverlayPack.release();
	}

	void read(INIFile* map);
	void write();
	void createOverlayFromData();
	void writeContentToINI(INIFile& file, PackType* pack, const std::string& sectionName);

	std::vector<byte> prepareDataForWriting(byte defaultByte, bool useIndex);

private:
	static OverlayPack* pInstance;
	OverlayPack();

	bool useOverlay = true;
	std::unique_ptr<PackType> pOverlayPack;
	std::unique_ptr<PackType> pOverlayDataPack;
	const static int F80_MAX = 262144;
};

