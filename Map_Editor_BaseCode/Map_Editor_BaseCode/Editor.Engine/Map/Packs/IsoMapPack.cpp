#include "stdafx.h"
#include "IsoMapPack.hpp"
#include "PackType.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../../Editor.FileSystem/MapFile/Compression/Base64.hpp"
#include "../../../Log.hpp"
#include "../../../Config.hpp"
#include "../../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"
#include <sstream>

/* static */ IsoMapPack* IsoMapPack::instance;

IsoMapPack::IsoMapPack(INISection* isoPack)
	:isoPack(isoPack)
{
	instance = this;

	if (isoPack)
	{
		hasIsoData = true;
	}
	else
	{
		Log::line("IsoMapPack5 isn't available, cannot read its data!", Log::DEBUG);
	}

	pack = new PackType(PackType::LZO);
}

IsoMapPack::~IsoMapPack()
{
	delete pack;
}

void IsoMapPack::read(INIFile* map)
{
	if (!hasIsoData) return;

	auto impSrc = base64_decodeSection(isoPack);
	pack->decompress(&impSrc[0], impSrc.size());
	std::vector<byte>& rawData = pack->getReadDest();

	auto pTile = reinterpret_cast<IsoMapPack5Tile*>(&rawData[0]);
	tiles.assign(pTile, pTile + rawData.size() / sizeof(IsoMapPack5Tile));

	map->deleteSection("IsoMapPack5");
}

void IsoMapPack::write()
{
	if (!hasIsoData) return;

	const int static structSize = sizeof(IsoMapPack5Tile);
	std::vector<byte> src(tiles.size() * structSize);

	memcpy(&src[0], &tiles[0], tiles.size() * structSize);

	pack->compress(&src[0], src.size());

}

void IsoMapPack::writeToINI(INIFile& file)
{
	if (!instance->hasIsoData)
	{
		Log::line("SECTION - IsoMapPack5 does not exist, will not write to map.", Log::DEBUG);
		return;
	}

	instance->write();
	PackType* pack = instance->getPack();
	std::string base64data = base64_encodeBytes(pack->getWriteDest());
	pack->clearWriteDest();
	
	unsigned int keyNumber = 0;
	for (unsigned int i = 0; i < base64data.length(); i += 70)
	{
		std::string value = base64data.substr(i, 70);
	//	if (keyNumber > 0)
			file.SetValue("IsoMapPack5", Log::toString(keyNumber), value);
		++keyNumber;
	}

	base64data.clear();
}
