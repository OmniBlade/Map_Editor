#pragma once
#include <map>
#include <memory>
#include "../../CsfFile/CSFFile.hpp"

struct FileProperties;

class CSFManager
{
public:
	static CSFManager* getManager();
	CSFFile* get(const std::string& fileName);
	CSFFile* cache(const std::string& fileName);
	std::wstring getValue(const std::string& name);

private:
	static CSFManager* manager;
	CSFManager();
	std::map<std::string, std::unique_ptr<CSFFile>> csfFiles;
};

