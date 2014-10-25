/*
 * INISection.cpp
 *
 *  Created on: 27 nov. 2013
 *      Author: Rik
 *	  Semester: CAR
 */

#include "stdafx.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <memory>
#include <iostream>
#include <algorithm>
#include "../../Log.hpp"

#include "INISection.hpp"

INISection::INISection(const std::string &id)
:sectionName(id) 
{

}

INISection::INISection(const INISection &other)
	: sectionName(other.sectionName), keys(other.keys), canDeleteFrom(other.canDeleteFrom)
{
	for (const auto& item : other.keyValueMap)
	{
		this->setValue(item.first.get(), item.second);
	}
}

void INISection::setValue(const std::string &key, std::string value)
{
	if (value.length())
	{
		auto it = getIter(key.c_str());
		if (it == keyValueMap.end())
		{
			keys.push_back(key);
			keyValueMap[ItemKey(keys.back(), true)] = std::move(value);
		}
		else
		{
			it->second = std::move(value);
		}
	}
	else
	{
		auto it = getIter(key.c_str());
		if (it != this->keyValueMap.end())
		{
			//free(const_cast<char*>(it->first.Value));
			keyValueMap.erase(it);
			keys.erase(std::find(keys.begin(), keys.end(), key));
		}
	}
}

void INISection::readDeletableStringValue(const char* key, std::string& variableToFill, const char* default_, bool uppercase)
{
	readStringValue(key, variableToFill, default_, uppercase);
	
	if (canDeleteFrom)
		deleteKeyValue(key);
}

void INISection::readStringValue(const char* key, std::string& varToFill, const char* default_ /*= ""*/, bool upperCase /* = false */)
{
	std::string returnString = getValue(key);

	if (upperCase)
		std::transform(returnString.begin(), returnString.end(), returnString.begin(), ::toupper);
	if (!returnString.empty())
		varToFill = std::move(returnString);
	else
		varToFill = default_;
}

void INISection::readDeletableIntValue(const char* key, int& varToFill, int default_ /* -1 */)
{
	readIntValue(key, varToFill, default_);
	
	if (canDeleteFrom)
		deleteKeyValue(key);
}

void INISection::readIntValue(const char* key, int& varToFill, int default_ /* = -1 */)
{
	const std::string& returnValue = getValue(key);

	if (!returnValue.empty())
		varToFill = atoi(returnValue.c_str());
	else
		varToFill = default_;
}

void INISection::readDeletableFloatValue(const char* key, float& varToFill, float default_ /* 1.0f */)
{
	readFloatValue(key, varToFill, default_);

	if (canDeleteFrom)
		deleteKeyValue(key);
}

void INISection::readFloatValue(const char* key, float& varToFill, float default_ /* = 1.0f */)
{
	const std::string& returnValue = getValue(key);

	if (!returnValue.empty())
		varToFill = (float) atof(returnValue.c_str());
	else
		varToFill = default_;
}

void INISection::readDeletableBoolValue(const char* key, bool& varToFill, bool default_ /* = false */)
{
	readBoolValue(key, varToFill, default_);
	
	if (canDeleteFrom)
		deleteKeyValue(key);
}

void INISection::readBoolValue(const char* key, bool& varToFill, bool default_ /* = false */)
{
	const std::string& value = getValue(key);

	varToFill = default_;
	if (value.empty())
		return;

	switch (toupper(value.front()))
	{
	case 'Y':
	case 'T':
	case '1':
			varToFill = true;
			return;
	case 'N':
	case 'F':
	case '0':
			varToFill = false;
			return;
	}
}

std::string const& INISection::getKey(int index, int default_ /*= 0*/)
{
	if (index < 0)
	{
		index = default_;
	}
	return keys[index];
}

std::string const INISection::getDeletableValue(const std::string& key)
{
	std::string ret = getValue(key.c_str());

	if (canDeleteFrom)
		deleteKeyValue(key.c_str());

	return ret;
}

std::string const& INISection::getValue(const char* key)
{
	auto& it = getIter(key);

	if (it != keyValueMap.end())
	{
		return it->second;
	}
	
	static const std::string empty; 
	return empty;
}

bool INISection::keyExists(const std::string& key)
{
	if (keyValueMap.find(key.c_str()) != keyValueMap.end())
	{
		return true;
	}
	return false;
}

bool INISection::valueExists(const std::string& key)
{
	auto& it = getIter(key.c_str());

	if (it != keyValueMap.end())
	{
		if (!it->second.empty())
			return true;
	}
	return false;
}

void INISection::dumpContent()
{
	Log::line();
	Log::line("Dumping content for:", Log::DEBUG);
	Log::line("[" + sectionName + "]", Log::DEBUG);
	for (const auto& it : keys)
	{
		Log::line(it + " = " + getValue(it), Log::DEBUG);
	}
	Log::line();
}

unsigned int INISection::totalSize() const
{
	unsigned int totalSize = 0;
	for (const auto& iter : keyValueMap)
	{
		totalSize += iter.second.length();
	}
	return totalSize;
}

int INISection::checkSumValues()
{
	int checksum = 0;
	for (auto& it : keys)
	{
		auto value = getValue(it.c_str());
		for (const auto& aChar : value)
		{
			checksum += aChar;
		}
	}
	return checksum;
}

int INISection::checkSumKeys()
{
	int checksum = 0;
	for (auto& it : keys)
	{
		for (const auto& aChar : it)
		{
			checksum += aChar;
		}
	}
	return checksum;
}

void INISection::clearAll(bool confirmation)
{
	if (confirmation)
	{
		keyValueMap.clear();
	}
}

void INISection::deleteKeyValue(const char* key)
{
	auto it = std::find(keys.begin(), keys.end(), key);
	if (it != keys.end())
	{
		keys.erase(it);
	}

	auto map_it = getIter(key);
	if (map_it != keyValueMap.end())
	{
		keyValueMap.erase(map_it);
	}
}
