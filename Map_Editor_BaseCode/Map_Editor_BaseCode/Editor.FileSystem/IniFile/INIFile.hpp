#pragma once
#include <map>
#include <vector>
#include <memory>
#include <string>
#include "../FileManager/FileWriter.h"
#include "INISection.hpp"


struct FileProperties;
class TextReader;

class INIFile {
public:
	INIFile();
	INIFile(const INIFile& other);
	INIFile(const FileProperties& props);
	INIFile(const FileProperties& props, INIFile* parentINI);
	INIFile(const FileProperties& props, TextReader* reader);
	~INIFile() { };

	void load(INIFile* parentINI, const FileProperties& props, TextReader* reader = nullptr);
	void SetValue(const char* section, std::string key, std::string value, bool insertAtFront = false);
	INISection* EnsureSection(const char* section, bool insertAtFront = false);
	INISection* getSection(const std::string &section) { return getSection(section.c_str()); };
	INISection* getSection(const char* section);
	bool sectionExists(const std::string &section);
	bool getLoaded() const;
	std::string& getININame();

	std::vector<std::string> getSectionList() { return sections; };
	int getSectionCount() { return sections.size(); };
	int getSectionCountWithoutDigest() { return sectionExists("Digest") ? sections.size() - 1 : sections.size(); };
	int generateAndGetCheckSum(int type = -1);

	void copyINITo(INIFile* file);
	void copyFromINI(INIFile* file);
	void addSectionByCopy(INISection* section, bool atFront = false) { for (const auto& it : *section) { SetValue(section->getSectionName().c_str(), it, section->getValue(it), atFront); } };
	void addSectionByCopyAfter(const std::string& name, INISection* section);
	
	void clearAll(bool confirmation);
	void deleteSection(const char* section);

	void dumpContent();

	void writeToSameFile(bool alphabetic = false);
	void writeToFile(const std::string& fullPath, bool alphabetic = false);
	void writeStartingComments(FileWriter* file);
	void writeAlphabetic(FileWriter* file);
	void writeVectorOrder(FileWriter* file);

	/* Adds a comment to the start of the map file, ONLY at the start of the file! */
	void addCommentAtTop(const std::string& comment) { comments.push_back(comment); };
	
	void setDeletableState(bool state) { canDeleteFrom = state; for (const auto& it : sections) { getSection(it)->setDeletableState(state); } };
	bool getDeletableState() { return canDeleteFrom; };

	void setupDigest();
	void setDigest(const std::string& digest) { this->digest = digest; };
	void setDigestForWriting(bool writeLock = false);
	//void setDigestForWritingManually(bool lock = false, bool flushed = false);
	std::string getDigest() { return digest; };
	void setDigestGenerationState(bool state) { generatesOwnDigest = state; };
	void setWritableState(bool state) { cannotWriteTo = state; };

private:
	struct ItemKey
	{
		ItemKey() = delete;

		ItemKey(const char* value, bool allocate = false) : Value(value), Allocated(allocate) {
			if (allocate) {
				this->Value = _strdup(value);
			}
		}

		ItemKey(const std::string& string, bool allocate = false) : ItemKey(string.c_str(), allocate) { }

		ItemKey(const ItemKey& other) = delete;

		ItemKey(ItemKey&& other) : Value(nullptr), Allocated(false) {
			*this = std::move(other);
		}

		~ItemKey() {
			if (Allocated) {
				free(const_cast<char*>(this->Value));
			}
		}

		ItemKey& operator = (const ItemKey& other) = delete;

		ItemKey& operator = (ItemKey&& other) {
			using std::swap;
			swap(this->Value, other.Value);
			swap(this->Allocated, other.Allocated);
			return *this;
		}

		bool operator < (const ItemKey& rhs) const {
			return strcmp(this->Value, rhs.Value) < 0;
		}

		const char* get() const { return this->Value; }

	private:
		const char* Value;
		bool Allocated;
	};

	bool isLoaded = false, canDeleteFrom = false, generatesOwnDigest = true, cannotWriteTo = false;
	std::string path, digest;
	std::map<ItemKey, std::unique_ptr<INISection>> sectionList;
	std::vector<std::string> includeINIs;
	std::vector<std::string> sections;
	std::vector<std::string> comments;
};

