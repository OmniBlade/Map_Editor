#pragma once

#include "BinaryReader.hpp"
#include <map>
#include <memory>
#include <string>

class RawFileSystem
{
public:
	RawFileSystem();
	~RawFileSystem();

	/*
		Gets the BinaryReader instance of a file, creates one if it doesn't exist
		NOTE: APPLIES ONLY TO THE GAME'S ROOT
		@param fileName The name of the file to get the Reader from
		@return A pointer to the instance of the BinaryReader of the file
	*/
	BinaryReader* getReaderOfFile(const std::string& fileName);
	
	/*
		Gets the BinaryReader instance of a file, creates one if it doesn't exist
		NOTE: APPLIES ONLY TO THE EDITOR'S ROOT
		@param fileName The name of the file to get the Reader from
		@return A pointer to the instance of the BinaryReader of the file
	*/
	BinaryReader* getReaderOfEditorFile(const std::string &fileName);
	
	/*
		Creates a BinaryReader instance for the file given in the parameter
		NOTE: APPLIES ONLY TO THE GAME'S ROOT
		@param fileName The name of the file to create the BinaryReader for
		@return A pointer to the instance of BinaryReader of the file, returns nullptr if the file does not exist
	*/
	BinaryReader* createReader(const std::string& fileName);
	
	/*
		Creates a BinaryReader instance for the file given in the parameter
		NOTE: APPLIES ONLY TO THE EDITOR'S ROOT
		@param fileName The name of the file to create the BinaryReader for
		@return A pointer to the instance of BinaryReader of the file, returns nullptr if the file does not exist
	*/
	BinaryReader* createEditorRootReader(const std::string& fileName);

	/*
		Checks whether the file given in the parameter exists in the GAME'S ROOT
		@param fileName The name of the file to check the existance of
		@return True if the file exists, false if it doesn't
	*/
	bool inGameRoot(const std::string& fileName);
	
	/*
		Checks whether the file given in the parameter exists in the EDITOR'S ROOT
		@param fileName The name of the file to check the existance of
		@return True if the file exists, false if it doesn't
	*/
	bool inEditorRoot(const std::string& fileName);
	
	/*
		Locates all the file's in the GAME'S ROOT and puts them in a vector
	*/
	void locateGameRootFiles();
	
	/*
		Locates all the file's in the EDITOR'S ROOT and puts them in a vector
	*/
	void locateEditorRootFiles();

private:
	std::map<std::string, std::unique_ptr<BinaryReader>> readerList;
	std::vector<std::string> gameRootFileNames;
	std::vector<std::string> editorRootFileNames;
};

