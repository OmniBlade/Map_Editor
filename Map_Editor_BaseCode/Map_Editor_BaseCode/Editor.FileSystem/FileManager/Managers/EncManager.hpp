#pragma once

#include <map>
#include <memory>
#include "../../EncFile/EncFile.hpp"

class INIFile;

class EncManager
{
public:
	static EncManager* instance();

	EncFile* get(const std::string& fileName);
	EncFile* cache(const std::string& fileName);
	INIFile* getAsINI(const std::string& fileName);
	INIFile* cacheAsINI(const std::string& fileName);

private:
	static EncManager* manager;
	EncManager();
	std::map<std::string, std::unique_ptr<EncFile>> encFiles;
};

