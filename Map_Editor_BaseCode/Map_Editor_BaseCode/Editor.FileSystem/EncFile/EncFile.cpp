#include "stdafx.h"
#include "EncFile.hpp"
#include <iostream>
#include <cstdlib>
#include "../FileManager/BinaryReader.hpp"
#include "../FileManager/FileSystem.hpp"
#include "../FileManager/Managers/INIManager.hpp"
#include "../IniFile/INIFile.hpp"

EncFile::EncFile(const FileProperties& props, const std::string& fileName, bool asINI /* = true */)
:encReader(props.reader), asINI(asINI)
{
	encReader->setOffset(props.offset);
	encReader->setSize(props.size);

	load(fileName);
}

void EncFile::load(const std::string& fileName)
{
	d();
	INIFile* file = new INIFile(fb);
	INIManager::getManager()->insert(fileName, file);

	//Don't need the vector anymore, so might as well empty it :)
	fb.clear();
	eb.clear();
}

void EncFile::d()
{
	fs = encReader->readInt(true);
	el = encReader->readInt(true);

	el ^= encReader->getFileSize();
	fs ^= el;

	gd();
	gf();

	unsigned int ei = 0;
	for (unsigned int i = 0; i < fb.size(); ++i)
	{
		fb[i] ^= eb[ei];

		if (ei == eb.size() - 1)
			ei = 0;
		ei++;
	}
}

void EncFile::gd()
{
	eb.resize(el);

	for (int i = 0; i < el; ++i)
	{
		eb[i] = encReader->readChar();
	}
}

void EncFile::gf()
{
	encReader->setOffset(encReader->getFileSize() - fs);
	fb.resize(fs);

	for (int i = 0; i < fs; ++i)
	{
		fb[i] = encReader->readChar();
	}
}
