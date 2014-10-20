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
class TextReader;

class INIFile {
public:
	INIFile();
	INIFile(const FileProperties& props);
	INIFile(const FileProperties& props, INIFile* parentINI);
	INIFile(const FileProperties& props, TextReader* reader);

	void load(INIFile* parentINI, const FileProperties& props, TextReader* reader = nullptr);
	void SetValue(const char* section, std::string key, std::string value);
	INISection* EnsureSection(const char* section);
	INISection* getSection(const std::string &section) { return getSection(section.c_str()); };
	INISection* getSection(const char* section);
	bool sectionExists(const std::string &section);
	bool getLoaded() const;
	std::string& getININame();

	std::vector<std::string> getSectionList() { return sections; };
	int getSectionCount() { return sections.size(); };
	int generateAndGetCheckSum(int type = -1);

	void addSectionByCopy(INISection* section) { for (const auto& it : *section) { SetValue(section->getSectionName().c_str(), it, section->getValue(it)); } };
	void deleteSection(const char* section);

	void dumpContent();

	void writeToSameFile(bool digest = false, bool writeLock = false, bool alphabetic = false);
	void writeToFile(const std::string& fullPath, bool digest = false, bool writeLock = false, bool alphabetic = false);
	void writeStartingComments(FileWriter* file);
	void writeAlphabetic(FileWriter* file);
	void writeVectorOrder(FileWriter* file);
	void setDigestForWriting(bool writeLock = false);

	/* Adds a comment to the start of the map file, ONLY at the start of the file! */
	void addCommentAtTop(const std::string& comment) { comments.push_back(comment); };

private:
	struct ItemKey
	{
		const char* Value;
		ItemKey(const char* value) : Value(value) {} bool operator < (const ItemKey& rhs) const { return strcmp(this->Value, rhs.Value) < 0; }
	};
	
	bool isLoaded = false;
	std::string path;
	std::map<ItemKey, std::shared_ptr<INISection>> sectionList;
	std::vector<std::string> includeINIs;
	std::vector<std::string> sections;
	std::vector<std::string> comments;
};

#endif /* INIFILE_HPP_ */
