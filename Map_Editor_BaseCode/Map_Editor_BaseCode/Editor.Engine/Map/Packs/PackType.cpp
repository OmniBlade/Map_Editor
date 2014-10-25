#include "stdafx.h"
#include "PackType.hpp"
#include "../../../Editor.FileSystem/MapFile/Compression/minilzo.h"
#include "../../../Editor.FileSystem/MapFile/Compression/Format80.h"
#include "../../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../../Log.hpp"
#include <iostream>
#include <algorithm>

PackType::PackType(Type compressionType)
:compression(compressionType)
{

}

PackType::~PackType()
{
	
}

void PackType::decompress(byte* src, size_t src_len)
{
	byte* destStart = nullptr;
	byte* dest = nullptr;

	if (compression == Type::F80)
	{
		readDest.resize(F80_MAX);
		destStart = &readDest[0];
		dest = &readDest[0];
	}

	size_t i = 0;
	while (i < src_len)
	{
		auto header = reinterpret_cast<unsigned short*>(&src[i]);
		auto InputSize = header[0];
		auto OutputSize = header[1];
		i += 4;

		auto dSize = readDest.size();

		if (compression == Type::LZO)
			readDest.resize(readDest.size() + OutputSize);

		unsigned long len = 0;
		if (compression == Type::F80)
			Format80::decompressInto(&src[i], InputSize, destStart, dest);
		else
			lzo1x_decompress(&src[i], InputSize, &readDest[dSize], &len, NULL);

		i += InputSize;
		if (compression == Type::F80)
		{
			dest += OutputSize;
			destStart += OutputSize;
		}
	}
}

void PackType::compress(byte* src, size_t src_len)
{
	static const size_t MaxBlockSize = 8192;
	const auto Size = src_len;

	if (compression == Type::F80)
		writeDest.resize((64 * Size + 62) / 63 + (4 * Size / MaxBlockSize) + 4);
	else
		writeDest.resize(Size + (Size / 16) + 64 + 3 + (Size / MaxBlockSize + 4));

	size_t WriteOffset = 0;
	for (size_t i = 0; i < Size;)
	{
		const auto BlockSize = std::min(Size - i, MaxBlockSize);

		const size_t HeaderAt = WriteOffset;
		WriteOffset += 4;
	
		unsigned long out_len = 0;
		if (compression == Type::F80)
		{
			out_len = Format80::compressInto(&src[i], BlockSize, &writeDest[WriteOffset]);;
		}
		else
		{
			byte wrkmem[4 * 16384];
			lzo1x_1_compress(&src[i], BlockSize, &writeDest[WriteOffset], &out_len, wrkmem);
		}

		auto Header = reinterpret_cast<word*>(&writeDest[HeaderAt]);
		Header[0] = static_cast<unsigned short>(out_len);
		Header[1] = static_cast<unsigned short>(BlockSize);

		WriteOffset += out_len;
		i += BlockSize;
	}

	writeDest.resize(WriteOffset);
}
