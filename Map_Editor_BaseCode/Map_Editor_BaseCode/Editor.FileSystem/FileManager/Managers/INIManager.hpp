#pragma once

#include <map>
#include <memory>
#include "../../INIFile/INIFile.hpp"

struct FileProperties;

class INIManager
{
public:
	INIManager();
	~INIManager();

	INIFile* get(const std::string& fileName);
	INIFile* cache(const std::string& fileName);
	
	void parseConfigFile(const std::string& _configPath);

private:
	std::map<std::string, std::unique_ptr<INIFile>> iniFiles;
};

