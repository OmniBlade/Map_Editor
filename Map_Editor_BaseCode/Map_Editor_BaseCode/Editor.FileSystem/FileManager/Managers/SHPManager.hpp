#pragma once

#include <map>
#include <memory>
#include "../../ShpFile/ShpFile.hpp"

class SHPManager
{
public:
	static SHPManager* getManager();

	ShpFile* cache(const std::string& fileName);
	ShpFile* get(const std::string& fileName);


private:
	static SHPManager* manager;
	SHPManager();
	std::map<std::string, std::unique_ptr<ShpFile>> shpFiles;
};

