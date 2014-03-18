#include "stdafx.h"
#include "TMPFile.hpp"
#include "../../GlobalData.hpp"
#include "../FileManager/FileSystem.hpp"
#include <iostream>

TMPFile::TMPFile(const std::string& _tmpName, const std::string& parentName, __int32 offset, int size)
:tmpName(_tmpName)//, tmpReader(GlobalData::MAIN_InstallDir + GlobalData::MAIN_BackSlash + parentName)
{
	//std::cout << "Constructor with offset" << std::endl;
	readHeader();
}

TMPFile::TMPFile(const std::string& _tmpName)
:tmpName(_tmpName)//, tmpReader(GlobalData::MAIN_InstallDir + GlobalData::MAIN_BackSlash + _tmpName)
{
	//std::cout << "Constructor without offset" << std::endl;
	readHeader();
}

TMPFile::TMPFile(const FileProperties& props)
:tmpReader(props.reader)
{
	tmpReader->setOffset(props.offset);
	tmpReader->setSize(props.size);
	readHeader();
}

void TMPFile::readHeader()
{
	width = tmpReader->readInt();
	height = tmpReader->readInt();
	tileWidth = tmpReader->readInt();
	tileHeight = tmpReader->readInt();
	amountOfFrames = width * height;

	std::vector<int> index;
	index.reserve(amountOfFrames);

	for (int i = 0; i < amountOfFrames; ++i)
	{
		//std::cout << "Loop #" << i + 1 << std::endl;
		index.push_back(tmpReader->readInt());
	}

	//Allocate spaces
	images.reserve(amountOfFrames);

	for (unsigned int i = 0; i < index.size(); ++i) 
	{
		if (index[i] > 0)
			images.insert(images.end(), std::make_unique<TMPImage>(tmpReader, index[i]));
		else
			images.insert(images.end(), nullptr);
	}
}