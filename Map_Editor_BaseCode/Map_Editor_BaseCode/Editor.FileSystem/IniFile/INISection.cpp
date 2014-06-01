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
:sectionName(id) {}

unsigned int INISection::size() const
{
	return this->keyValueMap.size();
}

const std::string& INISection::getSectionName() const
{
	return sectionName;
}

std::vector<std::string>::const_iterator INISection::begin() const
{
	return keys.begin();
}

std::vector<std::string>::const_iterator INISection::end() const
{
	return keys.end();
}

void INISection::setValue(const std::string &key, const std::string &value)
{
	if (value.length())
	{
		auto it = getIter(key);
		if (it == keyValueMap.end())
		{
			keyValueMap[key] = value;
			keys.push_back(key);
		}
		else
		{
			keyValueMap[key] = value;
		}
	}
	else
	{
		auto it = getIter(key);
		if (it != this->keyValueMap.end())
		{
			keyValueMap.erase(key);
			keys.erase(std::find(keys.begin(), keys.end(), key));
		}
	}
}

void INISection::readStringValue(const std::string &key, std::string& varToFill, const std::string &default_ /*= ""*/, bool upperCase /* = false */)
{
	std::string returnString = getValue(key);

	if (upperCase)
		std::transform(returnString.begin(), returnString.end(), returnString.begin(), ::toupper);
	if (!returnString.empty())
		varToFill = returnString;
	else
		varToFill = default_;
}

void INISection::readIntValue(const std::string& key, int& varToFill, int default_ /* = -1 */)
{
	std::string returnValue = getValue(key);

	if (!returnValue.empty())
		varToFill = atoi(returnValue.c_str());
	else
		varToFill = default_;
}

void INISection::readFloatValue(const std::string& key, float& varToFill, float default_ /* = 1.0f */)
{
	std::string returnValue = getValue(key);

	if (!returnValue.empty())
		varToFill = (float) atof(returnValue.c_str());
	else
		varToFill = default_;
}

void INISection::readBoolValue(const std::string& key, bool& varToFill, bool default_ /* = false */)
{
	std::string value = getValue(key);

	varToFill = default_;
	if (value.empty())
		return;

	std::transform(value.begin(), value.end(), value.begin(), ::toupper);
	switch (value.front())
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

std::string INISection::getKey(const std::string &key, const std::string &_default /*= ""*/)
{
	auto& it = getIter(key);

	if (it != this->keyValueMap.end())
	{
		return it->first;
	}
	return _default;
}

std::string& INISection::getValue(const std::string& key)
{
	auto& it = getIter(key);

	if (it != keyValueMap.end())
	{
		return it->second;
	}
	
	return std::string();
}

bool INISection::checkKeyExistance(const std::string& key)
{
	if (keyValueMap.find(key) != keyValueMap.end())
	{
		return true;
	}
	return false;
}

bool INISection::checkValueExistance(const std::string& key)
{
	auto& it = getIter(key);

	if (it != keyValueMap.end())
	{
		if (!it->second.empty())
			return true;
	}
	return false;
}

void INISection::dumpContent()
{
	Log::note();
	Log::note("[" + sectionName + "]", Log::DEBUG);
	for (const auto& iter : keyValueMap)
	{
		Log::note(iter.first + " = " + iter.second, Log::DEBUG);
	}
	Log::note();
}

std::map<std::string, std::string>::iterator INISection::getIter(const std::string& key)
{
	return keyValueMap.find(key);
}