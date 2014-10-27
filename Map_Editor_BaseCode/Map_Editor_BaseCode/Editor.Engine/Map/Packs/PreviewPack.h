#pragma once
#include <vector>
#include <memory>

class INISection;
class INIFile;
class PackType;

class PreviewPack
{
public:
	static PreviewPack* instance();
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

	void read(INIFile* map);
	void write();
	std::string sizeAsString();
	PackType* getPack() { return pack.get(); };
	int Width, Height;
	

private:
	static PreviewPack* pInstance;
	PreviewPack();

	bool hasPreview = true;
	std::unique_ptr<PackType> pack;
	std::vector<ColorEntry> imageBytes;
};

