#pragma once
#include <string>
#include <sstream>
/*
	Global data type used for X and Y (2D) coordination
*/
class Vector2D
{
public:

	std::string asString()
	{
		//(Y)YYXXX
		std::stringstream ret;

		ret << y;

		if (x < 100)
		{
			ret << '0';
		}
		if (x < 10)
		{
			ret << '0';
		}

		ret << x;

		return ret.str();
	}

	int x = 0;
	int y = 0;
};

