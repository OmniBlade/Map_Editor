#include "stdafx.h"
#include "PackType.hpp"
#include "../../Editor.FileSystem/MapFile/Base64.hpp"
#include "../../Editor.FileSystem/MapFile/minilzo.h"
#include "../../Editor.FileSystem/MapFile/Format80.h"
#include "../../Log.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include <iostream>

PackType::PackType(INISection* packSection, Type compressionType)
:packSection(packSection), compression(compressionType)
{

}

PackType::~PackType()
{
	
}

void PackType::decompress()
{
	//They are all Base64 encoded, so...
	src = base64_decodeSection(packSection);

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
		Log::note("Unable to decompress section with name '" + packSection->getSectionName() + "', unknown compression type set." , Log::DEBUG);
		dest.push_back(0); //lol srsly?
		break;
	}
}

//IsoMapPack5 and PreviewPack use this!
void PackType::decompressLZO()
{
	size_t i = 0;
	while (i < src.size())
	{
		auto header = reinterpret_cast<unsigned short*>(&src[i]);
		auto InputSize = header[0];
		auto OutputSize = header[1];
		i += 4;

		auto size = src.size();
		auto dSize = dest.size();

		dest.resize(dest.size() + OutputSize);

		unsigned long len = 0;
		lzo1x_decompress(&src[i], InputSize, &dest[dSize], &len, NULL);
		i += InputSize;
	}
}


//OverlayPack and OverlayDataPack use this!
void PackType::decompressF80()
{
	dest.resize(262144); //Test stuff for OverlayPack
	auto srcIter = src.begin();
	auto destIter = dest.begin();
	auto destBegin = dest.begin();

	while (srcIter < src.end())
	{
		unsigned short InputSize = 0, OutputSize = 0;

		InputSize |= *srcIter++;
		InputSize |= *srcIter++ << 8;
		OutputSize |= *srcIter++;
		OutputSize |= *srcIter++ << 8;

		Format80::decodeInto(srcIter, src.end(), destBegin, destIter);
		destBegin += OutputSize;
	}
}

void PackType::encode64()
{

}