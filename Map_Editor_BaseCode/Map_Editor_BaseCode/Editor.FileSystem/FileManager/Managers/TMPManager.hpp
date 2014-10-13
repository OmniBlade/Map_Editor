#pragma once

#include <memory>
#include <map>
#include "../../TmpFile/TMPFile.hpp"

class TMPManager
{
public:
	static TMPManager* instance();

	TMPFile* get(const std::string& fileName);
	TMPFile* cache(const std::string& fileName);
	bool exists(const std::string& fileName);

private:
	static TMPManager* manager;
	TMPManager();
	std::map<std::string, std::unique_ptr<TMPFile>> tmpFiles;
};

