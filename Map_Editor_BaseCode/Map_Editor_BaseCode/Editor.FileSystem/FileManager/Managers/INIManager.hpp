#pragma once

#include <map>
#include <memory>
#include "../../INIFile/INIFile.hpp"

struct FileProperties;

class INIManager
{
public:
	static INIManager* getManager();

	INIFile* get(const std::string& fileName);
	INIFile* cache(const std::string& fileName);

private:
	static INIManager* manager;
	INIManager();
	std::map<std::string, std::unique_ptr<INIFile>> iniFiles;
};

