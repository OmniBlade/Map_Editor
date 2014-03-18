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
//READING
	/* 
		Reads a string from a key
		@param key The key to return a string from
		@param _default The default value to return if the read value is incorrect
	*/
	std::string readStringValue(const std::string &key, const std::string &_default = "", bool upperCase = false) const;
	/*
		Reads an integer from a key
		@param key The key to return an int from
		@param _default The default value to return if the read value is incorrect
	*/
	int readIntValue(const std::string& key, int _default = 0) const;
	/*
		Reads a float value from a key
		@param key The key to return a float from
		@param _default The default value to return if the read value is incorrect

	*/
	float readFloatValue(const std::string& key, float _default = 0.0f) const;
	/*
		Reads a bool value for a key, looks at the first character and tells whether it is T(rue), Y(es), 1 or F(alse), N(o) or 0
		@param key The key to return a bool from
		@param _default The default value to return if the read value is incorrect
	*/
	bool readBoolValue(const std::string& key, bool _default = false) const;

	/* Dunno, probably obsolete by now (see checkKeyExistance) */
	std::string getKey(const std::string &key, const std::string &_default = "") const;

	/* Gets the next item in the list, perfect for not relying on the key */
	std::string getNextValue(const std::string& _default = "");

	bool checkKeyExistance(const std::string& _key);
	bool checkValueExistance(const std::string& _key);
	void dumpContent();

	unsigned int atItem = 0;
	std::string sectionName;
	std::map<std::string, std::string> keyValue;
};

#endif /* INISECTION_HPP_ */
