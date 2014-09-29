#include "stdafx.h"
#include "RawFileSystem.hpp"
#include <algorithm>
#include <windows.h>
#include <iostream>
#include "../../Config.hpp"
#include "../../Log.hpp"

RawFileSystem::RawFileSystem()
{
	locateEditorRootFiles();
}


RawFileSystem::~RawFileSystem()
{
}

BinaryReader* RawFileSystem::getReaderOfFile(const std::string& fileName)
{
	std::string capsFileName = fileName;
	std::transform(capsFileName.begin(), capsFileName.end(), capsFileName.begin(), ::toupper);

	auto it = this->readerList.find(capsFileName);
	if (it != this->readerList.end())
	{
		return it->second.get();
	}
	else
	{
		//Create file
		return createReader(capsFileName);
	}
}

BinaryReader* RawFileSystem::getReaderOfEditorFile(const std::string &fileName)
{
	std::string capsFileName = fileName;
	std::transform(capsFileName.begin(), capsFileName.end(), capsFileName.begin(), ::toupper);

	auto it = this->readerList.find(capsFileName);
	if (it != this->readerList.end())
	{
		return it->second.get();
	}
	else
	{
		//Create file
		return createEditorRootReader(capsFileName);
	}
}

//Used solely for the files in the root of the game!
BinaryReader* RawFileSystem::createReader(const std::string& fileName)
{
	if (!inGameRoot(fileName))
		return nullptr;

	readerList[fileName] = std::make_unique<BinaryReader>(Config::installDir + Config::backSlash + fileName);
	if (readerList[fileName].get()->isOpened == true)
		return readerList[fileName].get();
	else
	{
		readerList[fileName] = nullptr;
		return readerList[fileName].get();
	}
}

//Used solely for the files in the root of the map editor!
BinaryReader* RawFileSystem::createEditorRootReader(const std::string& fileName)
{
	if (!inEditorRoot(fileName))
		return nullptr;

	std::string filePath = Config::editorRoot + Config::backSlash + fileName;
	readerList[fileName] = std::make_unique<BinaryReader>(filePath);

	if (readerList[fileName].get()->isOpened == true)
		return readerList[fileName].get();
	else
	{
		readerList[fileName] = nullptr;
		return readerList[fileName].get();
	}
}

bool RawFileSystem::inGameRoot(const std::string& fileName)
{
	std::string capsFileName = fileName;
	std::transform(capsFileName.begin(), capsFileName.end(), capsFileName.begin(), ::toupper);

	for (unsigned int i = 0; i < gameRootFileNames.size(); ++i)
	{
		if (gameRootFileNames[i] == capsFileName)
			return true;
	}
	//std::cout << "File: " << capsFileName << " does not exist in the GAME root." << std::endl;
	return false;
}

bool RawFileSystem::inEditorRoot(const std::string& fileName)
{
	std::string capsFileName = fileName;
	std::transform(capsFileName.begin(), capsFileName.end(), capsFileName.begin(), ::toupper);

	for (unsigned int i = 0; i < editorRootFileNames.size(); ++i)
	{
		if (editorRootFileNames[i] == capsFileName)
			return true;
	}
	//std::cout << "File: " << fileName << " does not exist in the EDITOR root." << std::endl;
	return false;
}


void RawFileSystem::locateGameRootFiles()
{
	WIN32_FIND_DATA ffd;
	std::string rootFile = Config::installDir + Config::backSlash + "*.*";
	std::wstring dir(rootFile.begin(), rootFile.end());
	const wchar_t* dirChar = dir.c_str();

	HANDLE hFind = FindFirstFile(dirChar, &ffd);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		std::cout << "Invalid file!" << std::endl;
	}

	bool finished = false;
	int i = 1;
	while (!finished)
	{
		std::wstring wFileName = ffd.cFileName;
		std::string fileName(wFileName.begin(), wFileName.end());
		std::transform(fileName.begin(), fileName.end(), fileName.begin(), ::toupper);
		//std::cout << "Found GAME ROOT: " << fileName << std::endl;
		//std::cout << "Found in DIR: " << fileName << std::endl;
		gameRootFileNames.push_back(fileName);

		if (!FindNextFile(hFind, &ffd))
			finished = true;
		++i;
	}
	FindClose(hFind);
}

void RawFileSystem::locateEditorRootFiles()
{
	Log::line("Editor root is: " + Config::editorRoot, Log::DEBUG);
	WIN32_FIND_DATA ffd;
	std::string rootFile = Config::editorRoot + Config::backSlash + "*.*";
	std::wstring dir(rootFile.begin(), rootFile.end());
	const wchar_t* dirChar = dir.c_str();

	HANDLE hFind = FindFirstFile(dirChar, &ffd);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		std::cout << "Invalid file!" << std::endl;
	}

	//Log::line("==========================", Log::EXTRA);
	//Log::line("Files in editor root are:", Log::DEBUG);
	bool finished = false;
	int i = 1;
	while (!finished)
	{
		std::wstring wFileName = ffd.cFileName;
		std::string fileName(wFileName.begin(), wFileName.end());
		std::transform(fileName.begin(), fileName.end(), fileName.begin(), ::toupper);
		//std::cout << "Found EDITOR ROOT: " << fileName << std::endl;
		//std::cout << "Found in DIR: " << fileName << std::endl;
		if (fileName != "." && fileName != "..")
		{
			editorRootFileNames.push_back(fileName);
		//	Log::line(fileName, Log::DEBUG);
		}

		if (!FindNextFile(hFind, &ffd))
			finished = true;
		++i;
	}
	//Log::line("==========================", Log::EXTRA);
	FindClose(hFind);
}