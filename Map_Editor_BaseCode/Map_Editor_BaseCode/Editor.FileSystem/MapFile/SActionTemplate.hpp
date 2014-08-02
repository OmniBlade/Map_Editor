#pragma once
#include <string>

class INISection;
class ParamType;
class ParamCollection;

class SActionTemplate
{
public:
	SActionTemplate(INISection* section, ParamCollection* params);
	void parse(INISection* section, ParamCollection* params);

	//Stuff from the file
	int identifier;
	std::string name, description, tagCode, paramString;
	bool requiresAres, works;

	//Internal parsed stuff
	int P1 = 0;
	ParamType* param;
};
