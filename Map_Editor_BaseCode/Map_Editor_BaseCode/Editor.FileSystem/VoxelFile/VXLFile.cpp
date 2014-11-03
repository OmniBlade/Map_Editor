#include "stdafx.h"
#include "VXLFile.hpp"
#include "Section.h"
#include "../FileManager/FileSystem.hpp"
#include "../FileManager/BinaryReader.hpp"

VXLFile::VXLFile(const FileProperties& props)
:vxlReader(props.reader)
{
	vxlReader->setOffset(props.offset);
	vxlReader->setSize(props.size);
}


VXLFile::~VXLFile()
{
}

void VXLFile::read()
{

}