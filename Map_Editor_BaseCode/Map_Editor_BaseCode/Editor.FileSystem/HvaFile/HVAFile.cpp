#include "stdafx.h"
#include "HVAFile.hpp"
#include "../FileManager/FileSystem.hpp"
#include "../FileManager/BinaryReader.hpp"

HVAFile::HVAFile(const FileProperties& props)
:hvaReader(props.reader)
{
	hvaReader->setOffset(props.offset);
	hvaReader->setSize(props.size);
}


HVAFile::~HVAFile()
{
}
