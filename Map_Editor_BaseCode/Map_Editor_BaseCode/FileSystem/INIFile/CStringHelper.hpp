/*
 * CStringHelper.hpp
 *
 *  Created on: 2 dec. 2013
 *      Author: Rik
 *	  Semester: CAR
 */

#ifndef CSTRINGHELPER_HPP_
#define CSTRINGHELPER_HPP_

#include <string>

namespace StringHelper
{
	inline std::string& trimStart(std::string &string, const char* chars = " \t")
	{
		// skip until first non-whitespace
		auto start = string.find_first_not_of(chars);
		if (start != std::string::npos && start != 0)
		{
			string = string.substr(start);
		}
		return string;
	}

	inline std::string& trimEnd(std::string &string, const char* chars = " \t")
	{
		// take until first non-whitespace
		auto end = string.find_last_not_of(chars);
		if (end != std::string::npos && end != string.length() - 1)
		{
			string = string.substr(0, end + 1);
		}
		return string;
	}

	inline std::string& trim(std::string &string, const char* chars = " \t")
	{
		return trimStart(trimEnd(string, chars), chars);
	}
}

#endif /* CSTRINGHELPER_HPP_ */
