#include "stdafx.h"
#include "OverlayDataPack.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "PackType.hpp"

OverlayDataPack::OverlayDataPack(INISection* section)
	:section(section)
{
}


OverlayDataPack::~OverlayDataPack()
{
}

void OverlayDataPack::read()
{
	PackType pack(section, PackType::F80);
	pack.decompress();
}
