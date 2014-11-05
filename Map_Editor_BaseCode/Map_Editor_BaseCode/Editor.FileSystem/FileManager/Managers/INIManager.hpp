#pragma once

#include <map>
#include <vector>
#include <memory>
#include "../../IniFile/INIFile.hpp"

struct FileProperties;

class INIManager
{
public:
	static INIManager* instance();

	INIFile* get(const std::string& fileName);
	INIFile* cache(const std::string& fileName);
	INIFile* getRoot(const std::string& fileName);
	INIFile* cacheRoot(const std::string& fileName);
	void loadIncludeINI(const std::string& fileName, std::vector<std::string>& includes, INIFile* parent);
	void cacheIncluded(const std::string& fileName, INIFile* parent);
	void insert(const std::string& fileName, INIFile* file);
	INIFile* insertEmpty(const std::string& fileName);


	bool exists(const std::string& fileName) { if (iniFiles[fileName]) return true; return false; };

private:
	static INIManager* manager;
	INIManager();
	std::map< std::string, std::unique_ptr<INIFile> > iniFiles;
};

