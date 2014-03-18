#pragma once

#include <map>
#include <memory>
#include "../../ShpFile/ShpFile.hpp"

class SHPManager
{
public:
	SHPManager();
	~SHPManager();

	ShpFile* cache(const std::string& fileName);
	ShpFile* get(const std::string& fileName);


private:
	std::map<std::string, std::unique_ptr<ShpFile>> shpFiles;
};

