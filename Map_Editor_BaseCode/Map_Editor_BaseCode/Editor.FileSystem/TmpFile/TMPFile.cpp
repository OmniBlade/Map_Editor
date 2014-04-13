#include "stdafx.h"
#include "TMPFile.hpp"
#include "../../Config.hpp"
#include "../FileManager/FileSystem.hpp"
#include <iostream>

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
 		//if (i == 6)
//			std::cout << "";

		if (index[i] > 0)
			images.insert(images.end(), std::make_unique<TMPImage>(tmpReader, index[i]));
		else
			images.insert(images.end(), nullptr);
	}
}