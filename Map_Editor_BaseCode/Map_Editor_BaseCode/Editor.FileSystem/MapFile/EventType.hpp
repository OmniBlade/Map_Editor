#pragma once
#include <string>
#include <vector>

class INISection;
class ParamCollection;
class ParamType;

class EventType
{
public:
	EventType(INISection* section, ParamCollection* params);
	void parse(INISection* section, ParamCollection* params);

	//Stuff from the file
	int identifier;
	std::string name, description, tagCode, paramString;
	bool requiresAres, works;

	//Internal parsed stuff
	int P1 = 0, P2 = 0, P3 = 0;

	std::vector<ParamType*> paramList;
};

