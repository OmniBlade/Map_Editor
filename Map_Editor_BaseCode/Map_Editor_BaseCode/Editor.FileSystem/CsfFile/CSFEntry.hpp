#pragma once

#include <string>

class CSFEntry
{
public:
	CSFEntry(const std::wstring& value, const std::string& extraValue);

	std::wstring Value;
	std::string ExtraValue;

};

