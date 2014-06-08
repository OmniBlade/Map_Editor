#pragma once
#include <string>

class INISection;

class ActionTemplate
{
public:
	ActionTemplate(INISection* section);
	void parse(INISection* section);

	//Stuff from the file
	int identifier;
	std::string name, description, tagCode, paramString;
	bool requiresAres, works;

	//Internal parsed stuff
	int P1 = 0, P2 = 0, P3 = 0, P4 = 0, P5 = 0, P6 = 0, P7 = 0;
};

