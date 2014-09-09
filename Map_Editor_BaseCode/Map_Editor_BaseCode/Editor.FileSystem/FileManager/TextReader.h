#pragma once
#include <vector>

class BinaryReader;
struct FileProperties;

class TextReader
{
public:
	TextReader(const FileProperties& props);
	TextReader(const std::vector<char>& bytes);
	std::string readTextLine();
	bool checkEOF() { return index >= textBytes.size(); };

private:
	void readEntireFile(int size);

	size_t index;
	BinaryReader* textReader;
	std::vector<char> textBytes;
};

