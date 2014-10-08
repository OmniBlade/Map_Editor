#include "stdafx.h"
#include "PackType.hpp"
#include "../../Editor.FileSystem/MapFile/Base64.hpp"
#include "../../Editor.FileSystem/MapFile/minilzo.h"
#include "../../Editor.FileSystem/MapFile/Format80.h"
#include "../../Log.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include <iostream>
#include <algorithm>

PackType::PackType(INISection* packSection, Type compressionType)
:packSection(packSection), compression(compressionType)
{

}

PackType::~PackType()
{
	
}

void PackType::decompress()
{
	switch (compression)
	{
	case LZO:
		decompressLZO();
		break;
	case F80:
		decompressF80();
		break;
	case UNKNOWN:
	default:
		Log::line("Unable to decompress section with name '" + packSection->getSectionName() + "', unknown compression type set." , Log::DEBUG);
		readDest.push_back(0); //lol srsly?
		break;
	}
}

//IsoMapPack5 and PreviewPack use this!
void PackType::decompressLZO()
{
	size_t i = 0;
	while (i < readSrc.size())
	{
		auto header = reinterpret_cast<unsigned short*>(&readSrc[i]);
		auto InputSize = header[0];
		auto OutputSize = header[1];
		i += 4;

		auto size = readSrc.size();
		auto dSize = readDest.size();

		readDest.resize(readDest.size() + OutputSize);

		unsigned long len = 0;
		lzo1x_decompress(&readSrc[i], InputSize, &readDest[dSize], &len, NULL);
		i += InputSize;
	}
}


//OverlayPack and OverlayDataPack use this!
void PackType::decompressF80()
{
	readDest.resize(262144); //Test stuff for OverlayPack
	auto srcIter = readSrc.begin();
	auto destIter = readDest.begin();
	auto destBegin = readDest.begin();

	while (srcIter < readSrc.end())
	{
		unsigned short InputSize = 0, OutputSize = 0;

		InputSize |= *srcIter++;
		InputSize |= *srcIter++ << 8;
		OutputSize |= *srcIter++;
		OutputSize |= *srcIter++ << 8;

		Format80::decodeInto(srcIter, readSrc.end(), destBegin, destIter);
		destBegin += OutputSize;
	}
}

void PackType::compress()
{
	switch (compression)
	{
	case LZO:
		compressLZO();
		break;
	case F80:
		compressF80();
		break;
	case UNKNOWN:
	default:
		Log::line("Unable to compress section with name '" + packSection->getSectionName() + "', unknown compression type set.", Log::DEBUG);
		readDest.push_back(0); //lol srsly?
		break;
	}
}

void PackType::compressLZO()
{
	static const size_t MaxBlockSize = 8192;
	const auto Size = writeSrc.size();

	writeDest.resize(Size + (Size / 16) + 64 + 3 + (Size / MaxBlockSize + 4));

	size_t WriteOffset = 0;
	for (size_t i = 0; i < Size;) {
		const auto BlockSize = std::min(Size - i, MaxBlockSize);

		const size_t HeaderAt = WriteOffset;
		WriteOffset += 4;

		unsigned long out_len = 0;
		byte wrkmem[4 * 16384];
		lzo1x_1_compress(&writeSrc[i], BlockSize, &writeDest[WriteOffset], &out_len, wrkmem);

		auto Header = reinterpret_cast<word*>(&writeDest[HeaderAt]);
		Header[0] = out_len;
		Header[1] = BlockSize;

		WriteOffset += out_len;
		i += BlockSize;
	}

	writeDest.resize(WriteOffset);
}


void PackType::compressF80()
{

}

void PackType::encode64()
{
	encoded64 = base64_encodeBytes(writeDest);
}

void PackType::decode64()
{
	readSrc = base64_decodeSection(packSection);
}