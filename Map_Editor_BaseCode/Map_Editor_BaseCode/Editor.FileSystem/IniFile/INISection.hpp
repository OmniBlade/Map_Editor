/*
 * INISection.hpp
 *
 *  Created on: 27 nov. 2013
 *      Author: Rik
 *	  Semester: CAR
 */

#ifndef INISECTION_HPP_
#define INISECTION_HPP_

#include <vector>
#include <map>

class INISection {
public:
	INISection(const std::string &id);

	unsigned int size() const;
	const std::string& getSectionName() const;
	std::vector<std::string>::const_iterator begin() const;
	std::vector<std::string>::const_iterator end() const;
	void setValue(const std::string &key, const std::string &value);
//READING
	/* 
		Reads a string from a key
		@param key The key to return a string from
		@param _default The default value to return if the read value is incorrect
	*/
	void readStringValue(const std::string &key, std::string& variableToFill, const std::string &_default = "", bool upperCase = false);
	/*
		Reads an integer from a key
		@param key The key to return an int from
		@param _default The default value to return if the read value is incorrect
	*/
	void readIntValue(const std::string& key, int& variableToFill, int _default = -1);
	/*
		Reads a float value from a key
		@param key The key to return a float from
		@param _default The default value to return if the read value is incorrect

	*/
	void readFloatValue(const std::string& key, float& variableToFill, float _default = 1.0f);
	/*
		Reads a bool value for a key, looks at the first character and tells whether it is T(rue), Y(es), 1 or F(alse), N(o) or 0
		@param key The key to return a bool from
		@param _default The default value to return if the read value is incorrect
	*/
	void readBoolValue(const std::string& key, bool& variableToFill, bool _default = false);

	/* Dunno, probably obsolete by now (see checkKeyExistance) */
	std::string getKey(const std::string &key, const std::string &_default = "");

	/* */
	std::string& getValue(const std::string& key);

	/* Gets the next item in the list, perfect for not relying on the key */
	//std::string getNextValue(const std::string& _default = "");

	bool checkKeyExistance(const std::string& _key);
	bool checkValueExistance(const std::string& _key);
	void dumpContent();

private:
	unsigned int atItem = 0;
	std::string sectionName;
	std::map<std::string, std::string> keyValueMap;
	std::vector<std::string> keys;

	//To be removed :D
	//std::vector<std::pair<std::string, std::string>> keyValue;
	std::map<std::string, std::string>::iterator getIter(const std::string& key);
};

#endif /* INISECTION_HPP_ */
