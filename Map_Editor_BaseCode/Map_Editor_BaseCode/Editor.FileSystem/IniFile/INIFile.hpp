#ifndef INIFILE_HPP_
#define INIFILE_HPP_

#include <map>
#include <vector>
#include <memory>
#include <string>
#include "INISection.hpp"
#include "INIFile.hpp"
#include "../FileManager/FileWriter.h"

struct FileProperties;

class INIFile {
public:
	INIFile();
	INIFile(const FileProperties& props);
	INIFile(const FileProperties& props, INIFile* parentINI);
	INIFile(const std::vector<char>& bytes);

	void load(INIFile* parentINI, const FileProperties& props, const std::vector<char>* bytes = nullptr);
	void SetValue(const char* section, std::string key, std::string value);
	INISection* EnsureSection(const char* section);
	INISection* getSection(const std::string &section) { return getSection(section.c_str()); };
	INISection* getSection(const char* section);
	bool checkSectionExistance(const std::string &section);
	bool getLoaded() const;
	std::string& getININame();

	std::vector<std::string> getSectionList() { return sections; };

	void addSectionByCopy(INISection* section) { for (const auto& it : *section) { SetValue(section->getSectionName().c_str(), it, section->getValue(it)); } };
	void deleteSection(const char* section);

	void dumpContent();

	void writeToFile(const std::string& fullPath, bool alphabetic = true);

	/* Adds a comment to the start of the map file, ONLY at the start of the map file! */
	void addCommentAtTop(const std::string& comment) { comments.push_back(comment); };

private:
	struct ItemKey
	{
		const char* Value;
		ItemKey(const char* value) : Value(value) {} bool operator < (const ItemKey& rhs) const { return strcmp(this->Value, rhs.Value) < 0; }
	};
	
	int atEnc = 0;
	bool isLoaded = false;
	std::string iniName, mixName;
	std::map<ItemKey, std::shared_ptr<INISection>> sectionList;
	std::vector<std::string> includeINIs;
	std::vector<std::string> sections;
	std::vector<std::string> comments;
	std::vector<char> enc;
	FileWriter* iniWriter;
};

#endif /* INIFILE_HPP_ */
