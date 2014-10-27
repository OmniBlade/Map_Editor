#pragma once
#include <sstream>

struct CellStruct
{
	short X = 0;
	short Y = 0;

	std::string asString()
	{
		//(Y)YYXXX
		std::stringstream ret;

		ret << Y;

		if (X < 100)
		{
			ret << '0';
		}
		if (X < 10)
		{
			ret << '0';
		}

		ret << X;

		return ret.str();
	}

};