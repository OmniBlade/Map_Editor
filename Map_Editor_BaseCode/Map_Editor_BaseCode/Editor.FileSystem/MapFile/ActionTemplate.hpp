#pragma once
#include <string>
#include <vector>

class INISection;
class ParamCollection;
class ParamType;

class ActionTemplate
{
public:
	ActionTemplate(INISection* section, ParamCollection* params);
	void parse(INISection* section, ParamCollection* params);

	//Stuff from the file
	int identifier;
	std::string name, description, tagCode, paramString;
	bool requiresAres, works, framesIsSeconds, p7Waypoint = false;

	//Internal parsed stuff
	int P1 = 0, P2 = 0, P3 = 0, P4 = 0, P5 = 0, P6 = 0, P7 = 0;

	std::vector<ParamType*> paramList;
};

