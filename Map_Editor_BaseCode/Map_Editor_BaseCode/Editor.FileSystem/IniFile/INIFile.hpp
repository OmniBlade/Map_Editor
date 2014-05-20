#ifndef INIFILE_HPP_
#define INIFILE_HPP_

#include <map>
#include <vector>
#include <memory>
#include <string>
#include "INISection.hpp"
#include "INIFile.hpp"

class BinaryReader;
struct FileProperties;

class INIFile {
public:
	INIFile(const FileProperties& props);
	INIFile(const FileProperties& props, INIFile* parentINI);

	void loadInclude(INIFile* parentINI);
	void load(INIFile* parentINI);
	void SetValue(const std::string &section, const std::string &key, const std::string &value);
	INISection* EnsureSection(const std::string &section);
	INISection* getSection(const std::string &section);
	bool checkSectionExistance(const std::string &section);
	bool getLoaded() const;
	std::string& getININame();

	void dumpContent();

private:

	BinaryReader* iniReader;
	bool isLoaded = false;
	std::string iniName, mixName;
	std::map<std::string, std::unique_ptr<INISection>> sectionList;
	std::vector<std::string> includeINIs;
};

#endif /* INIFILE_HPP_ */
