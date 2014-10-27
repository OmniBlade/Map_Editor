#include "stdafx.h"
#include "PreviewPack.h"
#include "PackType.hpp"
#include "../../../Log.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Editor.FileSystem/MapFile/Compression/Base64.hpp"
#include "../../../Config.hpp"
#include "../../../Editor.FileSystem/FileManager/Managers/INIManager.hpp"

/* static */ PreviewPack* PreviewPack::pInstance;
/* static */ PreviewPack* PreviewPack::instance()
{
	if (!pInstance)
	{
		pInstance = new PreviewPack();
	}
	else
	{
		return pInstance;
	}
	return pInstance;
}

PreviewPack::PreviewPack()
{
	
}

void PreviewPack::read(INIFile* map)
{
	auto pPreviewPack = map->getSection("PreviewPack");
	auto pPreview = map->getSection("Preview");
	
	if (!pPreview || !pPreviewPack)
	{
		Log::line("PreviewPack or Preview does not exist!", Log::DEBUG);
		hasPreview = false;
		return;
	}

	pack = std::make_unique<PackType>(PackType::LZO);
	std::string sizeStr = pPreview->getValue("Size");
	LineSplitter split(sizeStr);

	split.pop(size.Left);
	split.pop(size.Top);
	split.pop(size.Width);
	split.pop(size.Height);

	auto decoded = base64_decodeSection(pPreviewPack);
	pack->decompress(&decoded[0], decoded.size());
	std::vector<byte>& rawData = pack->getReadDest();

	auto pColor = reinterpret_cast<ColorEntry*>(&rawData[0]);
	imageBytes.assign(pColor, pColor + rawData.size() / sizeof(ColorEntry));

	map->deleteSection("PreviewPack");
	map->deleteSection("Preview");

}

void PreviewPack::write()
{
	if (!hasPreview) return;

	const int static structSize = sizeof(ColorEntry);
	std::vector<byte> src(imageBytes.size() * structSize);

	memcpy(&src[0], &imageBytes[0], imageBytes.size() * structSize);

	pack->compress(&src[0], src.size());

}

void PreviewPack::writeToINI(INIFile& file)
{
	auto it = instance();

	if (!it->hasPreview)
	{
		Log::line("SECTION - PreviewPack does not exist, will not write to map.", Log::DEBUG);
		return;
	};

	file.SetValue("Preview", "Size", it->sizeAsString());

	it->write();
	PackType* pack = it->getPack();
	std::string base64data = base64_encodeBytes(pack->getWriteDest());
	pack->getWriteDest();

	unsigned int keyNumber = 0;
	for (unsigned int i = 0; i < base64data.length(); i += 70)
	{
		std::string value = base64data.substr(i, 70);
		file.SetValue("PreviewPack", Log::toString(keyNumber), value);
		++keyNumber;
	}

	base64data.clear();
}

std::string PreviewPack::sizeAsString()
{
	char buffer[512];
	sprintf_s(buffer, 512, "%d,%d,%d,%d",
		this->size.Left,
		this->size.Top,
		this->size.Width,
		this->size.Height
		);

	return buffer;
}