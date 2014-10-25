#pragma once
#include <string>
#include <vector>
#include "INameHelper.h"

class INISection;
class ParamCollection;
class ParamType;

class EventType : public INameHelper
{
public:
	EventType(INISection* section, ParamCollection* params);
	void parse(INISection* section, ParamCollection* params);

	/* From up top at INameHelper */
	std::string getNameWithParams();

	//Stuff from the file
	int identifier;
	std::string name, description, tagCode, paramString;
	bool requiresAres, works;

	//Internal parsed stuff
	int P1 = 0, P2 = 0, P3 = 0;

	std::vector<ParamType*> paramList;
	std::vector<ParamType*> nonZeroParamList; // For easy resolving of params
};

