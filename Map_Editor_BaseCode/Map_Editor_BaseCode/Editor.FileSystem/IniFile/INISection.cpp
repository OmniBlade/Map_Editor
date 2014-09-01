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

void INISection::setValue(const std::string &key, std::string value)
{
	if (value.length())
	{
		auto it = getIter(key.c_str());
		if (it == keyValueMap.end())
		{
			keys.push_back(key);
			keyValueMap[_strdup(keys.back().c_str())] = std::move(value);
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
			free(const_cast<char*>(it->first.Value));
			keyValueMap.erase(it);
			keys.erase(std::find(keys.begin(), keys.end(), key));
		}
	}
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

void INISection::readIntValue(const char* key, int& varToFill, int default_ /* = -1 */)
{
	const std::string& returnValue = getValue(key);

	if (!returnValue.empty())
		varToFill = atoi(returnValue.c_str());
	else
		varToFill = default_;
}

void INISection::readFloatValue(const char* key, float& varToFill, float default_ /* = 1.0f */)
{
	const std::string& returnValue = getValue(key);

	if (!returnValue.empty())
		varToFill = (float) atof(returnValue.c_str());
	else
		varToFill = default_;
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

bool INISection::checkKeyExistance(const std::string& key)
{
	if (keyValueMap.find(key.c_str()) != keyValueMap.end())
	{
		return true;
	}
	return false;
}

bool INISection::checkValueExistance(const std::string& key)
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
	Log::line("[" + sectionName + "]", Log::DEBUG);
	for (const auto& iter : keyValueMap)
	{
		//Log::line(iter.first + " = " + iter.second, Log::DEBUG);
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