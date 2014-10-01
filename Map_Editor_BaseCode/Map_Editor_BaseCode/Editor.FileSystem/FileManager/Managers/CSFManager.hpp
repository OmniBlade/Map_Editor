#pragma once
#include <map>
#include <memory>
#include "../../CsfFile/CSFFile.hpp"

struct FileProperties;

class CSFManager
{
public:
	static CSFManager* instance();
	CSFFile* get(const std::string& fileName);
	CSFFile* get(unsigned int index);
	CSFFile* cache(const std::string& fileName);
	std::wstring getValue(const std::string& name);

	int files();

private:
	static CSFManager* manager;
	CSFManager();
	//std::map<std::string, std::unique_ptr<CSFFile>> csfFiles;
	std::vector<std::unique_ptr<CSFFile>> csfFiles;
};

