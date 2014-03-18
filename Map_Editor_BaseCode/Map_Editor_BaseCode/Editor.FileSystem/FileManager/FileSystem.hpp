#pragma once

#include <vector>
#include <string>
#include <memory>
#include "RawFileSystem.hpp"
#include "Managers\MixManager.hpp"

struct FileProperties
{
	BinaryReader* reader = nullptr;
	int size = 0;
	int offset = 0;
};

class FileSystem
{
public:
	static FileSystem* getFileSystem();

	void assignPointers(RawFileSystem* _rawSystem, MIXManager* _mixManager);
	FileProperties getFile(const std::string& fileName);
	FileProperties getRootFile(const std::string& fileName);

private:
	static FileSystem* system;
	FileSystem();
	RawFileSystem* rawSystem;
	MIXManager* mixManager;

	BinaryReader* getReaderForEditorFile(const std::string& fileName);
	BinaryReader* getReaderForFile(const std::string& fileName);
	int getFileSize(const std::string& fileName);
	int getEditorFileSize(const std::string& fileName);
	int getFileOffset(const std::string& fileName);
	int getEditorFileOffset(const std::string& fileName);
};

