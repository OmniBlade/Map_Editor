#pragma once
#include <string>

class INISection;

class SActionTemplate
{
public:
	SActionTemplate(INISection* section);
	void parse(INISection* section);

	//Stuff from the file
	int identifier;
	std::string name, description, tagCode, paramString;
	bool requiresAres, works;

	//Internal parsed stuff
	int P1 = 0;
};

