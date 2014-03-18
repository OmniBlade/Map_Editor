#include "stdafx.h"
#include "Utils.hpp"

std::string Utils::toString(double _value)
{
	std::ostringstream stream;
	stream << _value;
	return stream.str();
}