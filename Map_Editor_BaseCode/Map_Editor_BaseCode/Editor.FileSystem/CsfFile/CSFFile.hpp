#pragma once

#include "CSFEntry.hpp"
#include <map>
#include <memory>
#include <vector>

struct FileProperties;
class BinaryReader;

class CSFFile
{
public:
	CSFFile(const FileProperties& props);

	enum CsvLanguage : byte
	{
		US = 0,
		UK,
		GERMAN,
		FRENCH,
		SPANISH,
		ITALIAN,
		JAPANESE,
		JABBERWOCKIE,
		KOREAN,
		CHINESE,
	};

	void parse();
	void setValue(const std::string& name, const std::wstring& value, const std::string& extraValue);
	bool get(const std::string& name, std::wstring& value);

	const unsigned int Identifier_FSC = 0x43534620;
	const unsigned int Identifier_LBL = 0x4c424c20;
	const unsigned int Identifier_RTS = 0x53545220;
	const unsigned int Identifier_WRTS = 0x53545257;

	int ID;
	int Flags1;
	int NumLabels;
	int NumExtraValues;
	int Zero;
	int Language;
	bool valid = false;

private:
	BinaryReader* csfReader;
	std::string iniName, mixName;
	std::map<std::string, std::unique_ptr<CSFEntry>> entryList;
	//std::vector<std::unique_ptr<CSFEntry>> entryList;
};

