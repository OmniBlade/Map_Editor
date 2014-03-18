#pragma once

#include <memory>
#include <map>
#include "../../TmpFile/TMPFile.hpp"

class TMPManager
{
public:
	TMPManager();
	~TMPManager();

	TMPFile* get(const std::string& fileName);
	TMPFile* cache(const std::string& fileName);

private:
	std::map<std::string, std::unique_ptr<TMPFile>> tmpFiles;
};

