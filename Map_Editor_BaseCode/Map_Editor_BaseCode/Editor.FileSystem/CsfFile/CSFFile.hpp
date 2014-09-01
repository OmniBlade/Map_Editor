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

	/*
		Is this even used? LOL
	*/
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

	/*
		Reads the CSF file only if the language is equal to the language of ra2md.csf
		and if the file is a CSF file type
	*/
	void parse();
	
	/*
		Creates a CSF file entry for the value and writes the actual value (the stuff you see in-game)
		and extra value
		
		@param name The name of the CSF string that will end up in the map
		@param value The actual value of the CSF string you'll see in-game and editor
		@param extraValue Additional and extra data that can be written as a string
	*/
	void setValue(const std::string& name, const std::wstring& value, const std::string& extraValue);
	
	/*
		Gets the CSF value for the name specified in the first parameter
		
		@param name The name of the CSF string to get
		@param value The variable of the CSF string value that will be filled
		@return True if the lookup and getting is valid, false if it isn't or if the string cannot be found
	*/
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

	std::map<std::string, std::unique_ptr<CSFEntry>> entryList;

private:
	BinaryReader* csfReader;
	std::string iniName, mixName;
};

