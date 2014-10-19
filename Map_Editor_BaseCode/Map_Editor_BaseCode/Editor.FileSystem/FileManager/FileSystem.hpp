#pragma once

#include <vector>
#include <string>
#include <memory>
#include "RawFileSystem.hpp"

struct FileProperties
{
	BinaryReader* reader = nullptr;
	int size = 0;
	int offset = 0;
	std::string path;
};

class FileSystem
{
public:
	static FileSystem* getFileSystem();
	
	/*
		After the instantiation of the file system, this function is called to add the RawFileSystem
		(the very lowest layer) to the class
		
		@param _rawSystem A pointer to the instance of RawFileSystem
	*/
	void assign(RawFileSystem* _rawSystem);
	
	/*
		Gets the file properties (BinaryReader, size and offset) for the file specified in the parameter
		from the GAME'S ROOT
		
		@param fileName The name of the file to return
		@return A struct containing the vital information of the file
	*/
	FileProperties getFile(const std::string& fileName);
	
	/*
		Gets the file properties (BinaryReader, size and offset) for the file specified in the parameter
		from the EDITOR'S ROOT
		
		@param fileName The name of the file to return
		@return A struct containing the vital information of the file
	*/
	FileProperties getRootFile(const std::string& fileName);
	
	/*
		NOTE: Most likely not in the right place!
		Gets the file version of the Yuri's Revenge main executable
		
		@param fullFileName The full path to the YR executable
		@return The version number as a wide string
	*/
	std::wstring getFileVersion(const std::string& fullFileName);

	bool exists(const std::string& fileName);
	std::string getFullPath(const std::string& fileName);
	std::string getFullEditorPath(const std::string& fileName);

private:
	static FileSystem* system;
	FileSystem();
	RawFileSystem* rawSystem;

	/*
		Gets the BinaryReader for the file specified in the parameter
		NOTE: APPLIES ONLY TO THE EDITOR'S ROOT
		@param fileName The name of the file to get the BinaryReader for
		@return A pointer to the instance of BinaryReader belonging to the file
	*/
	BinaryReader* getReaderForEditorFile(const std::string& fileName);
	
	/*
		Gets the BinaryReader for the file specified in the parameter
		NOTE: APPLIES ONLY TO THE GAME'S ROOT
		@param fileName The name of the file to get the BinaryReader for
		@return A pointer to the instance of BinaryReader belonging to the file
	*/
	BinaryReader* getReaderForFile(const std::string& fileName);
	
	/*
		Gets the file size for the file specified in the parameter
		NOTE: APPLIES ONLY TO THE GAME'S ROOT
		@param fileName The name of the file to get the size for
		@return The size of the file as an integer
	*/
	int getFileSize(const std::string& fileName);
	
	/*
		Gets the file size for the file specified in the parameter
		NOTE: APPLIES ONLY TO THE EDITOR'S ROOT
		@param fileName The name of the file to get the size for
		@return The size of the file as an integer
	*/
	int getEditorFileSize(const std::string& fileName);
	
	/*
		Gets the file offset for the file specified in the parameter
		NOTE: APPLIES ONLY TO THE GAME'S ROOT
		@param fileName The name of the file to get the offset for
		@return The offset of the file as an integer
	*/
	int getFileOffset(const std::string& fileName);
	
	/*
		Gets the file offset for the file specified in the parameter
		NOTE: APPLIES ONLY TO THE EDITOR'S ROOT
		@param fileName The name of the file to get the offset for
		@return The offset of the file as an integer
	*/
	int getEditorFileOffset(const std::string& fileName);
};

