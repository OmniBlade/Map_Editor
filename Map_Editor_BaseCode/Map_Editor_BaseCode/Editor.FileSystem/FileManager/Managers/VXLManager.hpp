#pragma once

#include <map>
#include <memory>
#include "../../VoxelFile/VXLFile.hpp"

class VXLManager
{
public:
	VXLManager();
	~VXLManager();

	VXLFile* get(const std::string& fileName);
	VXLFile* cache(const std::string& fileName);
	void cacheVPL(const std::string& fileName);

private:
	std::map<std::string, std::unique_ptr<VXLFile>> vxlFiles;
};

