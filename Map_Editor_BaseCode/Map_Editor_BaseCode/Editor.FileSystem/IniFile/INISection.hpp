/*
 * INISection.hpp
 *
 *  Created on: 27 nov. 2013
 *      Author: Rik
 *	  Semester: CAR
 */

#ifndef INISECTION_HPP_
#define INISECTION_HPP_

#include <string>
#include <vector>
#include <map>

class INISection {
public:
	INISection(const std::string &id);
	INISection(const INISection &other);
	~INISection() { };

	unsigned int size() const {	return this->keys.size(); };
	unsigned int totalSize() const;
	int checkSumKeys();
	int checkSumValues();
	const std::string& getSectionName() const { return sectionName; };
	const std::vector<std::string> getKeys() { return keys; };
	std::vector<std::string>::const_iterator begin() const { return keys.begin(); };
	std::vector<std::string>::const_iterator end() const { return keys.end(); };
	void setValue(const std::string &key, std::string value);

	void clearAll(bool confirmation);
	void deleteKeyValue(const char* key);
//READING
	/* 
		Reads a string from a key
		@param key The key to return a string from
		@param _default The default value to return if the read value is incorrect
	*/
	void readDeletableStringValue(const char* key, std::string& variableToFill, const char* default_ = "", bool uppercase = false);
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
	void readShortValue(const char* key, short& variableToFill, short default_ = -1);
	void readIntValue(const char* key, int& variableToFill, int _default = -1);
	void readDeletableIntValue(const char* key, int& variableToFill, int default_ = -1);
	/*
		Reads a float value from a key
		@param key The key to return a float from
		@param _default The default value to return if the read value is incorrect

	*/
	void readFloatValue(const char* key, float& variableToFill, float _default = 1.0f);
	void readDeletableFloatValue(const char* key, float& variableToFill, float default_ = 1.0f);
	/*
		Reads a bool value for a key, looks at the first character and tells whether it is T(rue), Y(es), 1 or F(alse), N(o) or 0
		@param key The key to return a bool from
		@param _default The default value to return if the read value is incorrect
	*/
	void readBoolValue(const char* key, bool& variableToFill, bool _default = false);
	void readDeletableBoolValue(const char* key, bool& variableToFill, bool default_ = false);

	/* Dunno, probably obsolete by now (see keyExists) */
	std::string const& getKey(int index, int default_ = 0);

	/* */
	std::string const getDeletableValue(const std::string& key);
	std::string const& getValue(const std::string& key) const { return getValue(key.c_str()); }
	std::string const& getValue(const char* key) const;

	/* Gets the next item in the list, perfect for not relying on the key */
	//std::string getNextValue(const std::string& _default = "");

	bool keyExists(const std::string& _key);
	bool valueExists(const std::string& _key);

	std::string getKeyValue(int index) { return keys[index] + "=" + getValue(keys[index].c_str()) + "\n"; };

	void dumpContent();

	void setDeletableState(bool state) { canDeleteFrom = state; };

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

	bool canDeleteFrom = false;
	std::string sectionName;
	std::map<ItemKey, std::string> keyValueMap;
	std::vector<std::string> keys;

	std::map<ItemKey, std::string>::iterator getIter(const char* key) { return keyValueMap.find(key); };
	std::map<ItemKey, std::string>::const_iterator getIter(const char* key) const { return keyValueMap.find(key); };
};

#endif /* INISECTION_HPP_ */
