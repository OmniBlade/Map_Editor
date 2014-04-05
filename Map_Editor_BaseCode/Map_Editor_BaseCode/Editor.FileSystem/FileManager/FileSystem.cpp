#include "stdafx.h" 
#include "FileSystem.hpp"
#include <iostream>
#include <algorithm>
#include "Managers\MixManager.hpp"

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

void FileSystem::assignPointers(RawFileSystem* _rawSystem)
{
	rawSystem = _rawSystem;
}

FileProperties FileSystem::getFile(const std::string& fileName)
{
	std::string fileNameCaps = fileName;
	std::transform(fileNameCaps.begin(), fileNameCaps.end(), fileNameCaps.begin(), ::toupper);

	FileProperties fileProp;
	fileProp.reader = getReaderForFile(fileNameCaps);
	fileProp.offset = getFileOffset(fileNameCaps);
	fileProp.size = getFileSize(fileNameCaps);

	return fileProp;
}

FileProperties FileSystem::getRootFile(const std::string& fileName)
{
	std::string fileNameCaps = fileName;
	std::transform(fileNameCaps.begin(), fileNameCaps.end(), fileNameCaps.begin(), ::toupper);

	FileProperties fileProp;
	fileProp.reader = getReaderForEditorFile(fileNameCaps);
	fileProp.offset = getEditorFileOffset(fileNameCaps);
	fileProp.size = getEditorFileSize(fileNameCaps);

	return fileProp;
}

BinaryReader* FileSystem::getReaderForFile(const std::string& fileName)
{
	if (auto res = rawSystem->getReaderOfFile(fileName))
		return res;
	else
		return MIXManager::getManager()->getReader(fileName);
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
		return MIXManager::getManager()->getSizeForFile(fileName);
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
		return MIXManager::getManager()->getOffsetForFile(fileName);
}

int FileSystem::getEditorFileOffset(const std::string& fileName)
{
	if (rawSystem->fileIsInEditorRoot(fileName))
		return 0;
	else
		return MIXManager::getManager()->getOffsetForFile(fileName);
}