#pragma once

#include <map>
#include <vector>
#include <memory>
#include "../../INIFile/INIFile.hpp"

struct FileProperties;

class INIManager
{
public:
	static INIManager* getManager();

	INIFile* get(const std::string& fileName);
	INIFile* get(const std::string& fileName, std::vector<std::string>& includes, INIFile* parent);
	INIFile* cache(const std::string& fileName);
	INIFile* cacheIncluded(const std::string& fileName, INIFile* parent);

private:
	static INIManager* manager;
	INIManager();
	std::map<std::string, std::unique_ptr<INIFile>> iniFiles;
};

