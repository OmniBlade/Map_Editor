#pragma once
#include <string>
#include <sstream>

class INameHelper
{
public:
	virtual std::string getNameWithParams() = 0;

	virtual std::string getReplacer(unsigned int number)
	{
		std::stringstream replacer;

		replacer << "%";

		if (number < 10)
		{
			replacer << "0";
		}

		replacer << number << "%";

		return replacer.str();
	}
};