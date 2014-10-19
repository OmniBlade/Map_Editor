#pragma once
#include <vector>
#include <string>

class BinaryReader;
struct FileProperties;

class EncFile
{
public:
	EncFile(const FileProperties& props, const std::string& fileName);
	
	void load(const std::string& fileName);

	void decrypt();
	void writeDecrypted();
	void fillEBytes(short len);
	void fillFileBytes(short len);

private:
	std::string path;
	BinaryReader* encReader;
	int rawSize;
	std::vector<char> bytes, eBytes;
};

