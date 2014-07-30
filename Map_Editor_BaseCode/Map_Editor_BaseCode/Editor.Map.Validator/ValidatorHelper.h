#pragma once
#include <string>

class ValidatorHelper
{
public:
	ValidatorHelper();

	static bool checkParam(int paramID, const std::string& value);
	static bool checkParam(int paramID, int value);
};

