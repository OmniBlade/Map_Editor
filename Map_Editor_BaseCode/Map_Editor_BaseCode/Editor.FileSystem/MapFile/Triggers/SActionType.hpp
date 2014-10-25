#pragma once
#include "INameHelper.h"

class INISection;
class ParamType;
class ParamCollection;

class SActionType : public INameHelper
{
public:
	SActionType(INISection* section, ParamCollection* params);
	void parse(INISection* section, ParamCollection* params);

	/* From up top at INameHelper */
	std::string getNameWithParams();

	//Stuff from the file
	int identifier;
	std::string name, description, paramString;
	bool requiresAres, works;

	//Internal parsed stuff
	int P1 = 0;
	ParamType* param;
};

