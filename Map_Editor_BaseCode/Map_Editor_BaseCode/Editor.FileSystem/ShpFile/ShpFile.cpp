#include "stdafx.h"
#include "ShpFile.hpp"
#include "Format3.hpp"
#include "../FileManager/FileSystem.hpp"
#include "../FileManager/BinaryReader.hpp"

#include <iostream>

ShpFile::ShpFile()
{
}

ShpFile::ShpFile(const FileProperties& props)
:shpReader(props.reader), fileSize(props.size)
{
	if (!props.reader) return;
	shpReader->setOffset(props.offset);
	shpReader->setSize(props.size);
	readHeader();
}

ShpFile::~ShpFile()
{
}

void ShpFile::readHeader()
{
	zero = shpReader->readShort();
	width = shpReader->readShort();
	height = shpReader->readShort();
	imageCount = shpReader->readShort();

	images.reserve(imageCount);
	for (unsigned int i = 0; i < imageCount; ++i)
	{
		images.insert(images.end(), std::make_unique<ShpImage>(shpReader, i));
	}
	readImages();
}

void ShpFile::readImages()
{
	for (unsigned int i = 0; i < images.size(); ++i)
	{
		ShpImage* currentImage = images[i].get();

		shpReader->setOffset(currentImage->dataOffset);
		int bytesToRead = width * height;

		if (currentImage->compressionType <= 1)
		{
			//std::cout << "Compression is of type <=1: " << (int) currentImage->compressionType << std::endl;
			currentImage->imageData = shpReader->readByteBlock(bytesToRead);
		}
		else if (currentImage->compressionType == 2)
		{
			//std::cout << "Compression is of type 2: " << (int) currentImage->compressionType << std::endl;
			int lineOffset = shpReader->getOffset();
			for (int y = 0; y < height; ++y)
			{
				unsigned short scanlineLength = (unsigned short)(shpReader->readUShort() - sizeof(unsigned short));
				std::vector<byte> tempBytes = shpReader->readByteBlockFromOffset(lineOffset, scanlineLength);
				currentImage->imageData.insert(currentImage->imageData.end(), tempBytes.begin(), tempBytes.end());
				lineOffset += scanlineLength;
			}
		}
		else if (currentImage->compressionType == 3)
		{
			//std::cout << "Compression is of type 3: " << (int) currentImage->compressionType << std::endl;
			int compressedEnd = fileSize;
			if (currentImage->frameIndex < (images.size() - 1))
				compressedEnd = images[currentImage->frameIndex + 1].get()->dataOffset;
			if (compressedEnd < currentImage->dataOffset)
				compressedEnd = fileSize;
			
			//std::cout << "Reading: " << compressedEnd - currentImage->dataOffset << " bytes, from: " << shpReader->getOffset() << std::endl;

			Format3::decode(shpReader->readByteBlock(compressedEnd - currentImage->dataOffset), currentImage->imageData, currentImage->width, currentImage->height);
		}
		else
		{
			std::cout << "Unknown compression type: " << currentImage->compressionType << "!" << std::endl;
		}
	}
}

ShpImage* ShpFile::get(int index)
{
	return images[index].get();
}