#pragma once
#include <string>

class INIFile;
class PackType;

class OverlayPack
{
public:
	OverlayPack(INIFile* file);
	~OverlayPack();

	static void writeToINI(INIFile& file);
	static OverlayPack* instance;

	void read();
	void write();
	void createOverlayFromData();
	void writeContentToINI(INIFile& file, PackType* pack, const std::string& sectionName);

	void prepareDataForWriting();

private:
	bool useOverlay = true;
	PackType* pOverlayPack;
	PackType* pOverlayDataPack;
	INIFile* file;
};

