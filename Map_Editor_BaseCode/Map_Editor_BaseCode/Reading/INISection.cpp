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

std::string INISection::getValue(const std::string &key, const std::string &_default /*= ""*/) const
{
	auto it = this->keyValue.find(key);
	if (it != this->keyValue.end())
	{
		return it->second;
	}
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
