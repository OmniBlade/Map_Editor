#include "stdafx.h"
#include "EncFile.hpp"
#include <iostream>
#include <cstdlib>
#include "../IniFile/INIFile.hpp"
#include "../FileManager/BinaryReader.hpp"
#include "../FileManager/TextReader.h"
#include "../FileManager/FileSystem.hpp"
#include "../FileManager/Managers/INIManager.hpp"
#include "../../Log.hpp"

EncFile::EncFile(const FileProperties& props, const std::string& fileName)
:encReader(props.reader)
{
	encReader->setOffset(props.offset);
	encReader->setSize(props.size);

	load(fileName);
}

void EncFile::load(const std::string& fileName)
{
	decrypt();
	TextReader* reader = new TextReader(bytes);
	INIFile* file = INIManager::instance()->insertEmpty(fileName);

	FileProperties props;
	file->load(nullptr, props, reader);

	/*
	d();
	INIFile* file = new INIFile(fb);
	INIManager::instance()->insert(fileName, file);

	//Don't need the vector anymore, so might as well empty it :)
	fb.clear();
	eb.clear();
	*/
}

void EncFile::decrypt()
{
	short len = encReader->readShort(true);
	len -= 0x15B3;

	if (encReader->getFileSize() < len + 0x152)
	{
		Log::line("Decryption of file with path: " + path + "' failed! File is too small.", Log::DEBUG);
		return;
	}

	encReader->setOffset(0x80);
	rawSize = encReader->readInt(true);
	rawSize -= 0x211D1AE3;

	if (encReader->getFileSize() < len + rawSize + 0x184)
	{
		Log::line("Decryption of file with path: " + path + "' failed! File is too small.", Log::DEBUG);
		return;
	}
	else
	{
		encReader->setOffset(0x104);
	
		fillFileBytes(rawSize);

		encReader->setOffset(rawSize + 0x184);

		fillEBytes(len);

		unsigned int encryptoIndex = 0;
		for (unsigned int i = 0; i < bytes.size(); ++i)
		{
			bytes[i] ^= eBytes[encryptoIndex];

			if (encryptoIndex == eBytes.size() - 1)
				encryptoIndex = 0;
			encryptoIndex++;
		}
		return;
	}	
}

void EncFile::fillEBytes(short len)
{
	encReader->readBlock(&eBytes[0], len);
	eBytes[0] = 2;
}

void EncFile::fillFileBytes(short len)
{
	encReader->readBlock(&bytes[0], len);
}
