#include "stdafx.h"
#include "VXLFile.hpp"
#include "../FileManager/FileSystem.hpp"
#include "../FileManager/BinaryReader.hpp"
#include "VPLFile.hpp"

VXLFile::VXLFile(const FileProperties& props)
:vxlReader(props.reader)
{
	vxlReader->setOffset(props.offset);
	vxlReader->setSize(props.size);
}


VXLFile::~VXLFile()
{
}
