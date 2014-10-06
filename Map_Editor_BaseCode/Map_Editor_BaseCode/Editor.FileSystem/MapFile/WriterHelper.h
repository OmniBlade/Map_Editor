#pragma once
#include <string>

class WriterHelper
{
public:

	enum BoolType
	{
		TRUEFALSE = 0,
		YESNO,
		BIT
	};

	static std::string getBoolString(bool state, BoolType type)
	{
		std::string ret;

		switch (type)
		{
		case TRUEFALSE:
			state ? ret = "true" : ret = "false";
			break;
		case YESNO:
			state ? ret = "yes" : ret = "no";
			break;
		case BIT:
			state ? ret = "1" : ret = "0";
			break;
		}
		
		return ret;

	}

};