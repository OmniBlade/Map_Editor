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

int INISection::size() const
{
	return this->keyValue.size();
}

const std::string& INISection::getSectionName() const
{
	return sectionName;
}

std::vector<std::pair<std::string, std::string>>::const_iterator INISection::begin() const
{
	return keyValue.begin();
}

std::vector<std::pair<std::string, std::string>>::const_iterator INISection::end() const
{
	return keyValue.end();
}

void INISection::setValue(const std::string &key, const std::string &value)
{
	if (value.length())
	{
		auto it = getIter(key);
		if (it == keyValue.end())
			keyValue.emplace_back(key, value);
	}
	else
	{
		auto it = getIter(key);
		if (it != this->keyValue.end())
		{
			this->keyValue.erase(it);
		}
	}
}

std::string INISection::readStringValue(const std::string &key, const std::string &_default /*= ""*/, bool upperCase /* = false */)
{
	std::string returnString = getValue(key, _default);

	if (upperCase)
		std::transform(returnString.begin(), returnString.end(), returnString.begin(), ::toupper);
	return returnString;
}

int INISection::readIntValue(const std::string& key, int _default /* = 0 */)
{
	std::string returnValue = getValue(key);
	if (returnValue != "")
	{
		int toReturn = atoi(returnValue.c_str());
		return toReturn;
	}
	else
	{
		return _default;
	}
}

float INISection::readFloatValue(const std::string& key, float _default /* = 0.0f */)
{
	std::string returnValue = getValue(key);
	if (returnValue != "")
	{
		float toReturn = atof(returnValue.c_str());
		return toReturn;
	}
	else
	{
		return _default;
	}
}

bool INISection::readBoolValue(const std::string& key, bool _default /* = false */)
{
	std::string defaultValue = "true";
	if (!_default)
		defaultValue = "false";

	std::string	value = getValue(key, defaultValue);
	std::transform(value.begin(), value.end(), value.begin(), ::toupper);
	switch (value.front())
	{
	case 'Y':
	case 'T':
	case '1':
		return true;
	case 'N':
	case 'F':
	case '0':
		return false;
	default:
		return _default;
	}
}

std::string INISection::getKey(const std::string &key, const std::string &_default /*= ""*/)
{
	auto it = getIter(key);

	if (it != this->keyValue.end())
	{
		return it->first;
	}
	return _default;
}

std::string INISection::getValue(const std::string& key, const std::string& default_ /* = ""*/)
{
	auto it = getIter(key);

	if (it != keyValue.end())
	{
		return it->second;
	}
	return default_;
}

std::string INISection::getNextValue(const std::string& _default)
{
	unsigned int localItem = 0;
	std::vector<std::pair<std::string, std::string>>::iterator iter;
	for (keyValue.begin(); iter != keyValue.end(); ++iter)
	//for (std::pair<const std::string, std::string>& _section : keyValue)
	{
		if (localItem == atItem)
		{
			atItem++;
			return iter->second;
		}
	}
	std::cout << "Looped through entire section, size of section: " << keyValue.size() << ", at item: " << atItem << std::endl;
	return _default;
}

bool INISection::checkKeyExistance(const std::string& key)
{
	auto it = std::find_if(keyValue.begin(), keyValue.end(), [key](std::pair<std::string, std::string>& item)
	{
		return item.first == key;
	});

	if (it != keyValue.end())
		return true;

	return false;
}

bool INISection::checkValueExistance(const std::string& key)
{
	auto it = getIter(key);

	if (it != keyValue.end())
	{
		if (it->second.length() > 0)
			return true;
	}
	else
		return false;
}

void INISection::dumpContent()
{
	//std::cout << "\n\n [" << sectionName << "]" << std::endl;
	Log::note("[" + sectionName + "]", Log::DEBUG);
	//for (std::pair<const std::string,std::string>& _section: keyValue)
	//{
//		Log::note("Key: " + _section.first + " | Value: " + _section.second, Log::DEBUG);
//		//std::cout << "Key: " << _section.first << " | Value: " << _section.second << std::endl;
	//}
}

std::vector<std::pair<std::string, std::string>>::iterator INISection::getIter(const std::string& key)
{
	auto it = std::find_if(keyValue.begin(), keyValue.end(), [key](std::pair<std::string, std::string>& item)
	{
		return item.first == key;
	});

	return it;
}