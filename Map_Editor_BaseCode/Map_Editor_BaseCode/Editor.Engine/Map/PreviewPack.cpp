#include "stdafx.h"
#include "PreviewPack.h"
#include "PackType.hpp"
#include "../../Log.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"

/* static */ PreviewPack* PreviewPack::instance;

PreviewPack::PreviewPack(INIFile* map)
{
	pPreviewPack = map->getSection("PreviewPack");
	pPreview = map->getSection("Preview");
	instance = this;

	if (pPreviewPack && pPreview)
	{
		hasPreview = true;
	}
	else
	{
		Log::line("PreviewPack and Preview aren't available, cannot read its data!", Log::DEBUG);
		return;
	}

	pack = new PackType(pPreviewPack, PackType::LZO);
}


PreviewPack::~PreviewPack()
{
	delete instance;
}

void PreviewPack::read()
{
	if (!hasPreview) return;

	std::string sizeStr = pPreview->getValue("Size");
	LineSplitter split(sizeStr);

	split.pop(size.Left);
	split.pop(size.Top);
	split.pop(size.Width);
	split.pop(size.Height);

	pack->decode64();
	pack->decompress();
	std::vector<byte>& rawData = pack->getReadDest();

	auto pColor = reinterpret_cast<ColorEntry*>(&rawData[0]);
	imageBytes.assign(pColor, pColor + rawData.size() / sizeof(ColorEntry));
}

void PreviewPack::write()
{
	if (!hasPreview) return;

	const int static structSize = sizeof(ColorEntry);
	std::vector<byte> src(imageBytes.size() * structSize);

	memcpy(&src[0], &imageBytes[0], imageBytes.size() * structSize);

	pack->setWriteSrc(src);
	pack->compress();

	pack->encode64();
}

void PreviewPack::writeToINI(INIFile& file)
{
	if (!instance->hasPreview)
	{
		Log::line("SECTION - PreviewPack does not exist, will not write to map.", Log::DEBUG);
		return;
	};

	file.SetValue("Preview", "Size", instance->sizeAsString());

	PackType* pack = instance->getPack();
	std::string base64data = std::move(pack->getEncodedString());

	unsigned int keyNumber = 0;
	for (unsigned int i = 0; i < base64data.length(); i += 70)
	{
		std::string value = base64data.substr(i, 70);
		file.SetValue("PreviewPack", Log::toString(keyNumber), value);
		++keyNumber;
	}
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