#pragma once

#include <string>
#include <vector>
#include "../FileSystem/INIFile/INIFile.hpp"

class INIFileHandler
{
public:
	INIFileHandler();
	~INIFileHandler();

	void createVirtualINI(const std::string& _ININame, const std::string& parentName = "", __int32 offset = 0, int size = 0);
	INIFile* getAnINIFile(const std::string& _ININame);

	void parseConfigFile(const std::string& _configPath);

private:
	INIFile* currentINI;
	std::vector<INIFile*> iniFiles;
};

