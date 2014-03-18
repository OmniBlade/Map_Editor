#include "stdafx.h"
#include <algorithm>
#include <iostream>
#include "VPLFile.hpp"
#include "../FileManager/FileSystem.hpp"


/* static */ VPLFile* VPLFile::vplFile;
/* static */ VPLFile* VPLFile::getVPL()
{
	if (vplFile)
		return vplFile;
	else
		vplFile = new VPLFile();
	return vplFile;
}

VPLFile::VPLFile()
{
}

void VPLFile::setProperties(const FileProperties& props)
{
	vplReader = props.reader;
	vplReader->setOffset(props.offset);
	vplReader->setSize(props.size);
}

VPLFile::~VPLFile()
{
}

void VPLFile::read()
{
	firstRemap = vplReader->readUInt();
	lastRemap = vplReader->readUInt();
	numSections = vplReader->readUInt();
	unknown = vplReader->readUInt();
	vplReader->discardBytes(768);

	std::cout << "First remap: " << firstRemap << std::endl;
	std::cout << "Last remap: " << lastRemap << std::endl;
	std::cout << "Num sections: " << numSections << std::endl;

	for (unsigned int i = 0; i < numSections; ++i)
	{
		lookupSections.push_back(vplReader->readByteBlock(256));
	}
}

byte VPLFile::getPaletteIndex(byte normal, byte maxNormal, byte color)
{
	int vplSection = (int) (std::min((int) normal, maxNormal - 1) * numSections / maxNormal);

	return lookupSections[vplSection][color];
}


/*public byte GetPaletteIndex(byte normal, byte maxNormal, byte color) {
	if (!_parsed) Parse();
	int vplSection = (int)(Math.Min(normal, maxNormal - 1) * _numSections / maxNormal);
	return _lookupSections[vplSection][color];*/