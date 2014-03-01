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
#include "../../Reading/BinaryReader.hpp"

class INIFile {
public:
	INIFile(const std::string& _iniName, const std::string& _directory);
	INIFile(const std::string& _iniName);
	INIFile(const std::string& _iniName, const std::string& parentName, __int32 offset, int size);

	virtual ~INIFile();

	void load();
	void SetValue(const std::string &section, const std::string &key, const std::string &value);
	INISection* EnsureSection(const std::string &section);
	INISection* getSection(const std::string &section);
	std::map<std::string, std::shared_ptr<INISection>>* getSectionMap();
	bool checkSectionExistance(const std::string &section);
	bool checkSectionExistanceAgain(const std::string &section);
	bool getLoaded() const;
	std::string& getININame();

private:
	BinaryReader iniReader;
	//__int32 offset = 0;
	bool isLoaded = false;
	std::string iniName, mixName;
	std::map<std::string ,std::shared_ptr<INISection>> sectionList;
};

#endif /* INIFILE_HPP_ */
