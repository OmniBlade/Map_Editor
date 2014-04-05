#pragma once

#include <map>
#include <memory>
#include "../../VoxelFile/VXLFile.hpp"

class VXLManager
{
public:
	static VXLManager* getManager();

	VXLFile* get(const std::string& fileName);
	VXLFile* cache(const std::string& fileName);
	void cacheVPL(const std::string& fileName);

private:
	static VXLManager* manager;
	VXLManager();
	std::map<std::string, std::unique_ptr<VXLFile>> vxlFiles;
};

