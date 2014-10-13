#pragma once
#include <vector>

class INISection;
class INIFile;
class PackType;

class PreviewPack
{
public:
	static PreviewPack* instance;
	static void writeToINI(INIFile& file);

	struct ColorEntry
	{
		byte b;
		byte g;
		byte r;
	};

	struct Size
	{
		int Left;
		int Top;
		int Width;
		int Height;
	} size;

	PreviewPack(INIFile* map);
	~PreviewPack();

	void read();
	void write();
	std::string sizeAsString();
	PackType* getPack() { return pack; };
	int Width, Height;
	

private:
	bool hasPreview = false;
	INISection* pPreviewPack;
	INISection* pPreview;

	PackType* pack;
	std::vector<ColorEntry> imageBytes;
};

