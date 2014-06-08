#pragma once
#include <string>

class INISection;

class EventTemplate
{
public:
	EventTemplate(INISection* section);
	void parse(INISection* section);

	//Stuff from the file
	int identifier;
	std::string name, description, tagCode, paramString;
	bool requiresAres, works;

	//60,2,1,SAPC
	//Internal parsed stuff
	int P1 = 0, P2 = 0, P3 = 0;
};

