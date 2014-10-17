#pragma once
#include <string>
#include <fstream>

class FileWriter
{
public:
	FileWriter(const std::string& fullPath);

	void writeByte(byte aByte);
	void writeBuffer(const byte* bytes, unsigned int amount);
	void writeBuffer(const char* bytes, unsigned int amount);

	/* Flushes the data, closes the file */
	void close() { file.flush();  file.close(); };
	/* (Re-)opens the file */
	void open() { file.open(fullPath); };
	/* Flush the bytes to safety */
	void flush() { file.flush(); };

private:
	bool canWrite = true;
	std::ofstream file;
	std::string fullPath;
};

