#include "stdafx.h"
#include "OverlayPack.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../Types/Overlay.h"
#include "PackType.hpp"

/* static */ OverlayPack* OverlayPack::instance;

OverlayPack::OverlayPack(INIFile* file)
	:file(file)
{
	instance = this;
}

OverlayPack::~OverlayPack()
{
	delete pOverlayPack; 
	delete pOverlayDataPack;
}

void OverlayPack::read()
{
	INISection* dataPack = file->getSection("OverlayDataPack");
	INISection* pack = file->getSection("OverlayPack");

	if (!pack || !dataPack)
	{
		Log::line("OverlayDataPack or OverlayPack does not exist, unable to parse Overlay!", Log::DEBUG);
		useOverlay = false;
		return;
	}

	pOverlayDataPack = new PackType(dataPack, PackType::F80);
	pOverlayPack = new PackType(pack, PackType::F80);

	pOverlayPack->decode64();
	pOverlayDataPack->decode64();

	pOverlayPack->decompress();
	pOverlayDataPack->decompress();

	//map_write_test.ini
}

void OverlayPack::write()
{
	if (!useOverlay)
	{
		return;
	}

	prepareDataForWriting();

	pOverlayPack->compress();
	pOverlayDataPack->compress();

	pOverlayPack->encode64();
	pOverlayDataPack->encode64();
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
		//int x = 512 * 2 - 2; x >= 0; x--
		//unsigned int x = 0; x < 511; ++x
		for (unsigned int x = 0; x < 511; ++x)
		{
			int index = x + y * 512;
			if (overlayDest[index] != 0xFF)
			{
				Overlay::Array.createOverlay(x, y, overlayDest[index], overlayDataDest[index]);
			}
		}
	}

	//All parsing is done, no need for the bytes to occupy the memory for so long
	//pOverlayPack->clearReadDest();
	//pOverlayDataPack->clearReadDest();
}

void OverlayPack::writeToINI(INIFile& file)
{
	if (!instance->useOverlay) return;
	//OverlayPack, then OverlayDataPack
	instance->writeContentToINI(file, instance->pOverlayPack, "OverlayPack");
	instance->writeContentToINI(file, instance->pOverlayDataPack, "OverlayDataPack");
}

void OverlayPack::writeContentToINI(INIFile& file, PackType* pack, const std::string& sectionName)
{
	std::string base64data = std::move(pack->getEncodedString());

	unsigned int keyNumber = 0;
	for (unsigned int i = 0; i < base64data.length(); i += 70)
	{
		std::string value = base64data.substr(i, 70);
		file.SetValue(sectionName.c_str(), Log::toString(keyNumber), value);
		++keyNumber;
	}
}

void OverlayPack::prepareDataForWriting()
{
	std::vector<byte> rawDataBytes(262144, 0);		//OverlayDataPack
	std::vector<byte> rawBytes(262144, 0xFF);		//OverlayPack

	for (auto& it : Overlay::Array.objectList)
	{
		rawDataBytes[it->loc.x + it->loc.y * 512] = it->overlayFrame;
		rawBytes[it->loc.x + it->loc.y * 512] = it->overlayIndex;
	}

	pOverlayDataPack->setWriteSrc(rawDataBytes);
	pOverlayPack->setWriteSrc(rawBytes);
}