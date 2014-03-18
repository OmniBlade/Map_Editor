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

	BinaryReader* getReaderOfFile(const std::string& fileName);
	BinaryReader* getReaderOfEditorFile(const std::string &fileName);
	BinaryReader* createReader(const std::string& fileName);
	BinaryReader* createEditorRootReader(const std::string& fileName);

	bool fileIsInGameRoot(const std::string& fileName);
	bool fileIsInEditorRoot(const std::string& fileName);
	void locateGameRootFiles();
	void locateEditorRootFiles();

private:
	std::map<std::string, std::unique_ptr<BinaryReader>> readerList;
	std::vector<std::string> gameRootFileNames;
	std::vector<std::string> editorRootFileNames;
};

