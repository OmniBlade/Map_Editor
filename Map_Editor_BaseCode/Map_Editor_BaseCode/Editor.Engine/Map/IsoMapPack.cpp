#include "stdafx.h"
#include "IsoMapPack.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "PackType.hpp"

IsoMapPack::IsoMapPack(INISection* isoPack)
	:isoPack(isoPack)
{

}


IsoMapPack::~IsoMapPack()
{
}

void IsoMapPack::read()
{
	PackType pack(isoPack, PackType::LZO);
	pack.decompress();
	std::vector<byte>& rawData = pack.getDest();

	auto pTile = reinterpret_cast<IsoMapPack5Tile*>(&rawData[0]);
	tiles.assign(pTile, pTile + rawData.size() / sizeof(IsoMapPack5Tile));	
}