/*
 * INIFile.hpp
 *
 *  Created on: 27 nov. 2013
 *      Author: Rik
 *	  Semester: CAR
 */

#ifndef INIFILE_HPP_
#define INIFILE_HPP_

#include <map>
#include <memory>
#include <string>

#include "INISection.hpp"
#include "BinaryReader.hpp"

class INIFile {
public:
	INIFile():isLoaded(false) {};
	INIFile(BinaryReader* iniReader, __int32 offset);
	virtual ~INIFile();

	void load(const std::string &filename);
	void SetValue(const std::string &section, const std::string &key, const std::string &value);
	INISection* EnsureSection(const std::string &section);
	INISection* getSection(const std::string &section);
	std::map<std::string, std::shared_ptr<INISection>>* getSectionMap();
	bool checkSectionExistance(const std::string &section);
	bool checkSectionExistanceAgain(const std::string &section);
	bool getLoaded() const;

private:
	BinaryReader* iniReader;
	bool isLoaded = false;
	std::string filePath;
	std::map<std::string ,std::shared_ptr<INISection>> sectionList;
};

#endif /* INIFILE_HPP_ */
