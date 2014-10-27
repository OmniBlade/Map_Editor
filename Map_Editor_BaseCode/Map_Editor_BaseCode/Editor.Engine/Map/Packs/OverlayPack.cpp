#include "stdafx.h"
#include "OverlayPack.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../../Editor.FileSystem/MapFile/Compression/Base64.hpp"
#include "../../../Config.hpp"
#include "../../Types/Overlay.h"
#include "PackType.hpp"

/* static */ OverlayPack* OverlayPack::pInstance;
/* static */ OverlayPack* OverlayPack::instance()
{
	if (!pInstance)
	{
		pInstance = new OverlayPack();
	}
	else
	{
		return pInstance;
	}
	return pInstance;
}

OverlayPack::OverlayPack()
{

}

void OverlayPack::read(INIFile* map)
{
	INISection* dataPack = map->getSection("OverlayDataPack");
	INISection* pack = map->getSection("OverlayPack");

	if (!pack || !dataPack)
	{
		Log::line("OverlayDataPack or OverlayPack does not exist, unable to parse Overlay!", Log::DEBUG);
		useOverlay = false;
		return;
	}

	pOverlayDataPack = std::make_unique<PackType>(PackType::F80);
	pOverlayPack = std::make_unique<PackType>(PackType::F80);

	std::vector<byte> opSrc = base64_decodeSection(pack);
	std::vector<byte> opdSrc = base64_decodeSection(dataPack);

	pOverlayPack->decompress(&opSrc[0], opSrc.size());
	pOverlayDataPack->decompress(&opdSrc[0], opdSrc.size());

	map->deleteSection("OverlayPack");
	map->deleteSection("OverlayDataPack");
}

void OverlayPack::write()
{
	if (!useOverlay)
	{
		return;
	}

	pOverlayPack->compress(&prepareDataForWriting(0xFF, true)[0], F80_MAX);
	pOverlayDataPack->compress(&prepareDataForWriting(0, false)[0], F80_MAX);

}

void OverlayPack::createOverlayFromData()
{
	if (!useOverlay)
	{
		return;
	}
	auto overlayDest = pOverlayPack->getReadDest();
	auto overlayDataDest = pOverlayDataPack->getReadDest();

	for (unsigned int y = 0; y < 511; ++y)
	{
		for (unsigned int x = 0; x < 511; ++x)
		{
			int index = x + y * 512;
			if (overlayDest[index] != 0xFF)
			{
				Overlay::Array.createOverlay(x, y, overlayDest[index], overlayDataDest[index]);
			}
		}
	}
}

void OverlayPack::writeToINI(INIFile& file)
{
	auto it = instance();
	if (!it->useOverlay)
	{
		Log::line("SECTION - OverlayData and OverlayDataPack don't exist, will not write to map.", Log::DEBUG);
		return;
	}
	it->write();
	//OverlayPack, then OverlayDataPack
	it->writeContentToINI(file, it->pOverlayPack.get(), "OverlayPack");
	it->writeContentToINI(file, it->pOverlayDataPack.get(), "OverlayDataPack");
}

void OverlayPack::writeContentToINI(INIFile& file, PackType* pack, const std::string& sectionName)
{
	std::string base64data = base64_encodeBytes(pack->getWriteDest());
	pack->clearWriteDest();

	unsigned int keyNumber = 0;
	for (unsigned int i = 0; i < base64data.length(); i += 70)
	{
		std::string value = base64data.substr(i, 70);
		//if (keyNumber > 0)
			file.SetValue(sectionName.c_str(), Log::toString(keyNumber), value);
		++keyNumber;
	}
	base64data.clear();
}

std::vector<byte> OverlayPack::prepareDataForWriting(byte defaultByte, bool useIndex)
{
	std::vector<byte> ret(262144, defaultByte);

	for (auto& it : Overlay::Array.objectList)
	{
		ret[it->loc.x + it->loc.y * 512] = useIndex ? it->overlayIndex : it->overlayFrame;
	}

	return ret;
}