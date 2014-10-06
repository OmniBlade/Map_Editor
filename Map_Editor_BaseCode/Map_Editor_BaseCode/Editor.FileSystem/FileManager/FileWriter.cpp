#include "stdafx.h"
#include "FileWriter.h"
#include "../../Config.hpp"
#include "../../Log.hpp"

FileWriter::FileWriter(const std::string& fullPath)
:fullPath(fullPath)
{
	file.open(fullPath, std::ios::binary | std::ios::out, _SH_DENYNO);
	
	if (!file.is_open())
	{
		Log::line("CRITICAL - Unable to open file with full path: " + fullPath, Log::DEBUG);
		Log::line("Cannot continue writing, aborting!", Log::EXTRA);
		return;
	}
}

void FileWriter::writeByte(byte aByte)
{
	file.write(reinterpret_cast<char*>(&aByte), sizeof(char*));
}

void FileWriter::writeBuffer(const char* buffer, unsigned int amount)
{
	file.write(&buffer[0], amount);
}

void FileWriter::writeBuffer(const byte* buffer, unsigned int amount)
{
	file.write(reinterpret_cast<const char*>(&buffer[0]), amount);
}