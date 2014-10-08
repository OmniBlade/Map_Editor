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

	//word header[] = { pack->getWriteDest().size(), src.size() };
	//src.insert(src.begin(), reinterpret_cast<byte*>(header), reinterpret_cast<byte*>(header)+4);

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

	/*
	int rowNum = 1;
			for (int i = 0; i < image_base64.Length; i += 70) {
				section.SetValue(rowNum++.ToString(CultureInfo.InvariantCulture), image_base64.Substring(i, Math.Min(70, image_base64.Length - i)));
			}
	*/

}
