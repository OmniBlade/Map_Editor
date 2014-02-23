/*
 * INISection.hpp
 *
 *  Created on: 27 nov. 2013
 *      Author: Rik
 *	  Semester: CAR
 */

#ifndef INISECTION_HPP_
#define INISECTION_HPP_

#include <map>

class INISection {
public:
	INISection(const std::string &id);

	int size() const;
	const std::string& getSectionName() const;
	std::map<std::string, std::string> getMap() const;
	std::map<std::string, std::string>::const_iterator begin() const;
	std::map<std::string, std::string>::const_iterator end() const;
	void setValue(const std::string &key, const std::string &value);
	std::string getValue(const std::string &key, const std::string &_default = "") const;
	std::string getKey(const std::string &key, const std::string &_default = "") const;
	bool checkKeyExistance(const std::string& _key);
	bool checkValueExistance(const std::string& _key);
	void dumpContent();

	std::string sectionName;
	std::map<std::string, std::string> keyValue;
};

#endif /* INISECTION_HPP_ */
