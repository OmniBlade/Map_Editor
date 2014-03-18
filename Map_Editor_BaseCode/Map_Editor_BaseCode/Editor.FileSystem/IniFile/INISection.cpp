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

std::map<std::string, std::string> INISection::getMap() const
{
	return keyValue;
}

std::map<std::string, std::string>::const_iterator INISection::begin() const
{
	return keyValue.begin();
}

std::map<std::string, std::string>::const_iterator INISection::end() const
{
	return keyValue.end();
}

void INISection::setValue(const std::string &key, const std::string &value)
{
	if (value.length())
	{
		this->keyValue[key] = value;
	}
	else
	{
		auto it = this->keyValue.find(key);
		if (it != this->keyValue.end())
		{
			this->keyValue.erase(it);
		}
	}
}

std::string INISection::readStringValue(const std::string &key, const std::string &_default /*= ""*/, bool upperCase /* = false */) const
{
	auto it = this->keyValue.find(key);
	if (it != this->keyValue.end())
	{
		std::string returnString = it->second;
		if (upperCase)
			std::transform(returnString.begin(), returnString.end(), returnString.begin(), ::toupper);
		return returnString;
	}
	return _default;
}

int INISection::readIntValue(const std::string& key, int _default /* = 0 */) const
{
	auto it = this->keyValue.find(key);
	if (it != this->keyValue.end())
	{
		int toReturn = atoi(it->second.c_str());
		return toReturn;
	}
	else
	{
		return _default;
	}
}

float INISection::readFloatValue(const std::string& key, float _default /* = 0.0f */) const
{
	auto it = this->keyValue.find(key);
	if (it != this->keyValue.end())
	{
		float toReturn = atof(it->second.c_str());
		return toReturn;
	}
	else
	{
		return _default;
	}
}

bool INISection::readBoolValue(const std::string& key, bool _default /* = false */) const
{
	auto it = this->keyValue.find(key);
	if (it != this->keyValue.end())
	{
		std::string	value = it->second;
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
	else
		return _default;
}

std::string INISection::getKey(const std::string &key, const std::string &_default /*= ""*/) const
{
	auto it = this->keyValue.find(key);
	if (it != this->keyValue.end())
	{
		return it->first;
	}
	return _default;
}

std::string INISection::getNextValue(const std::string& _default)
{
	unsigned int localItem = 0;
	for (std::map< std::string, std::string, std::less< int > >::const_iterator iter = keyValue.begin(); iter != keyValue.end(); ++iter)
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

bool INISection::checkKeyExistance(const std::string& _key)
{
	for (std::pair<const std::string,std::string>& _section: keyValue)
	{
		if(_section.first == _key)
		{
			return true;
		}
	}
	return false;
}

bool INISection::checkValueExistance(const std::string& _key)
{
	for (std::pair<const std::string,std::string>& _section: keyValue)
	{
		if(checkKeyExistance(_key) && _section.second.size() > 0)
		{
			return true;
		}
	}
	return false;
}

void INISection::dumpContent()
{
	std::cout << "\n\n [" << sectionName << "]" << std::endl;
	for (std::pair<const std::string,std::string>& _section: keyValue)
	{
		std::cout << "Key: " << _section.first << " | Value: " << _section.second << std::endl;
	}
}
