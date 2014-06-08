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

	unsigned int size() const {	return this->keyValueMap.size(); };
	const std::string& getSectionName() const { return sectionName; };
	std::vector<std::string>::const_iterator begin() const { return keys.begin(); };
	std::vector<std::string>::const_iterator end() const { return keys.end(); };
	void setValue(const std::string &key, std::string value);
//READING
	/* 
		Reads a string from a key
		@param key The key to return a string from
		@param _default The default value to return if the read value is incorrect
	*/
	void readStringValue(const char* key, std::string& variableToFill, const char* default_ = "", bool upperCase = false);
	void readStringValue(const char* key, std::string& variableToFill, const std::string& default_, bool upperCase = false)
	{
		readStringValue(key, variableToFill, default_.c_str(), upperCase);
	};
	void readStringValue(const std::string& key, std::string& variableToFill, const char* default_ = "", bool upperCase = false)
	{
		readStringValue(key.c_str(), variableToFill, default_, upperCase);
	};
	void readStringValue(const std::string& key, std::string& variableToFill, const std::string& default_, bool upperCase = false)
	{
		readStringValue(key.c_str(), variableToFill, default_.c_str(), upperCase);
	};
	
	/*
		Reads an integer from a key
		@param key The key to return an int from
		@param _default The default value to return if the read value is incorrect
	*/
	void readIntValue(const char* key, int& variableToFill, int _default = -1);
	/*
		Reads a float value from a key
		@param key The key to return a float from
		@param _default The default value to return if the read value is incorrect

	*/
	void readFloatValue(const char* key, float& variableToFill, float _default = 1.0f);
	/*
		Reads a bool value for a key, looks at the first character and tells whether it is T(rue), Y(es), 1 or F(alse), N(o) or 0
		@param key The key to return a bool from
		@param _default The default value to return if the read value is incorrect
	*/
	void readBoolValue(const char* key, bool& variableToFill, bool _default = false);

	/* Dunno, probably obsolete by now (see checkKeyExistance) */
	std::string const& getKey(int index, int default_ = 0);

	/* */
	std::string const& getValue(const std::string& key) { return getValue(key.c_str()); }
	std::string const& getValue(const char* key);

	/* Gets the next item in the list, perfect for not relying on the key */
	//std::string getNextValue(const std::string& _default = "");

	bool checkKeyExistance(const std::string& _key);
	bool checkValueExistance(const std::string& _key);
	void dumpContent();

private:
	struct ItemKey
	{
		const char* Value;
		ItemKey(const char* value) : Value(value) {} bool operator < (const ItemKey& rhs) const { return strcmp(this->Value, rhs.Value) < 0; }
	};
	
	unsigned int atItem = 0;
	std::string sectionName;
	std::map<ItemKey, std::string> keyValueMap;
	std::vector<std::string> keys;

	//To be removed :D
	//std::vector<std::pair<std::string, std::string>> keyValue;
	std::map<ItemKey, std::string>::iterator getIter(const char* key) { return keyValueMap.find(key); };
};

#endif /* INISECTION_HPP_ */
