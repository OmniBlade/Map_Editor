#include "stdafx.h" 
#include "FileSystem.hpp"
#include <iostream>
#include <algorithm>
#include "Managers\MixManager.hpp"
#include "../../Log.hpp"
#include "Windows.h"

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

void FileSystem::assign(RawFileSystem* _rawSystem)
{
	rawSystem = _rawSystem;
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
	std::string fileNameCaps = fileName;
	std::transform(fileNameCaps.begin(), fileNameCaps.end(), fileNameCaps.begin(), ::toupper);

	FileProperties fileProp;
	fileProp.reader = getReaderForEditorFile(fileNameCaps);
	fileProp.offset = getEditorFileOffset(fileNameCaps);
	fileProp.size = getEditorFileSize(fileNameCaps);

	return fileProp;
}

std::wstring FileSystem::getFileVersion(const std::string& fullFileName)
{
	return L"NOT SUPPORTED UNTIL PROPER DETERMINATION IS FOUND";

	FileProperties props = getFile(fullFileName);
	if (props.size == 4813072)
	{
		return L"YR - 1.001";
	}
	else if (props.size == 4808976)
	{
		return L"YR - 1.000";
	}

	return L"YR - UNKNOWN... MODIFIED?";
}

BinaryReader* FileSystem::getReaderForFile(const std::string& fileName)
{
	if (auto res = rawSystem->getReaderOfFile(fileName))
		return res;
	else
		return MIXManager::instance()->getReader(fileName);
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
		return MIXManager::instance()->getSizeForFile(fileName);
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
	if (rawSystem->inGameRoot(fileName))
		return 0;
	else
		return MIXManager::instance()->getOffsetForFile(fileName);
}

int FileSystem::getEditorFileOffset(const std::string& fileName)
{
	if (rawSystem->inEditorRoot(fileName))
		return 0;
	else
		return MIXManager::instance()->getOffsetForFile(fileName);
}