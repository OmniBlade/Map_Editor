#pragma once
#include "../Managers/WWList.hpp"
#include <string>

class Movie
{
public:
	static WWList<Movie> Array;

	Movie();
	void parse(const std::string& id, const std::string& name);
	std::string ID, Name;
	std::wstring WUIName;
	bool valid = true;
};

