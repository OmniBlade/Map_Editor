#include "stdafx.h"
#include "IsoMapPack.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "PackType.hpp"
#include <sstream>
#include "../../Log.hpp"

/* static */ IsoMapPack* IsoMapPack::instance;

IsoMapPack::IsoMapPack(INISection* isoPack)
	:isoPack(isoPack)
{
	instance = this;
	pack = new PackType(isoPack, PackType::LZO);
}

void IsoMapPack::read()
{
	pack->decode64();
	pack->decompress();
	std::vector<byte>& rawData = pack->getReadDest();

	pack->dumpReadDest();

	pack->setWriteSrc(pack->getReadDest());
	pack->compress();

	pack->setReadSrc(pack->getWriteDest());
	pack->compress();

	pack->dumpReadDest();


	auto pTile = reinterpret_cast<IsoMapPack5Tile*>(&rawData[0]);
	tiles.assign(pTile, pTile + rawData.size() / sizeof(IsoMapPack5Tile));	
}

void IsoMapPack::write()
{
	const int static structSize = sizeof(IsoMapPack5Tile);
	std::vector<byte> src(tiles.size() * structSize);

	memcpy(&src[0], &tiles[0], tiles.size() * sizeof(structSize));

	pack->setWriteSrc(src);
	pack->compress();

	pack->encode64();
}

void IsoMapPack::writeToINI(INIFile& file)
{
	PackType* pack = instance->getPack();
	std::string base64data = std::move(pack->getEncodedString());
	
	unsigned int keyNumber = 0;
	for (unsigned int i = 0; i < base64data.length(); i += 70)
	{
		std::string value = base64data.substr(i, 70);
		file.SetValue("IsoMapPack5", Log::toString(keyNumber), value);
		++keyNumber;
	}
}
