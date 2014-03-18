#include "stdafx.h" 
#include "FileSystem.hpp"
#include <iostream>
#include <algorithm>

/* static */ FileSystem* FileSystem::system;
/* static */ FileSystem* FileSystem::getFileSystem()
{
	if (system)
		return system;
	else
		system = new FileSystem();
	
	return system;
}


FileSystem::FileSystem()
{
}

void FileSystem::assignPointers(RawFileSystem* _rawSystem, MIXManager* _mixManager)
{
	rawSystem = _rawSystem;
	mixManager = _mixManager;
}

FileProperties FileSystem::getFile(const std::string& fileName)
{
	FileProperties fileProp;
	fileProp.reader = getReaderForFile(fileName);
	fileProp.offset = getFileOffset(fileName);
	fileProp.size = getFileSize(fileName);

	return fileProp;
}

FileProperties FileSystem::getRootFile(const std::string& fileName)
{
	FileProperties fileProp;
	fileProp.reader = getReaderForEditorFile(fileName);
	fileProp.offset = getEditorFileOffset(fileName);
	fileProp.size = getEditorFileSize(fileName);

	return fileProp;
}

BinaryReader* FileSystem::getReaderForFile(const std::string& fileName)
{
	if (auto res = rawSystem->getReaderOfFile(fileName))
		return res;
	else
		return mixManager->getReader(fileName);
}

BinaryReader* FileSystem::getReaderForEditorFile(const std::string& fileName)
{
	if (auto res = rawSystem->getReaderOfEditorFile(fileName))
		return res;

	return nullptr;
}


int FileSystem::getFileSize(const std::string& fileName)
{
	if (auto res = rawSystem->getReaderOfFile(fileName)) //rawSystem->fileIsInGameRoot(fileName))
		return res->getFileSize();
	else
		return mixManager->getSizeForFile(fileName);
}

int FileSystem::getEditorFileSize(const std::string& fileName)
{
	if (auto res = rawSystem->getReaderOfEditorFile(fileName))
		return res->getFileSize();
	else
		return 0;
}

int FileSystem::getFileOffset(const std::string& fileName)
{
	if (rawSystem->fileIsInGameRoot(fileName))
		return 0;
	else
		return mixManager->getOffsetForFile(fileName);
}

int FileSystem::getEditorFileOffset(const std::string& fileName)
{
	if (rawSystem->fileIsInEditorRoot(fileName))
		return 0;
	else
		return mixManager->getOffsetForFile(fileName);
}