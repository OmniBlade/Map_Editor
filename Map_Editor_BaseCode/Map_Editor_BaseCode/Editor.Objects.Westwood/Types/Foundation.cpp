#include "stdafx.h"
#include "Foundation.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Editor.FileSystem/IniFile/CStringHelper.hpp"
#include "../../Config.hpp"
#include <sstream>
#include <vector>

Foundation::Foundation()
{

}

Foundation::~Foundation()
{
}

void Foundation::parse(INISection* section)
{
	std::string foundation = section->getValue("Foundation");
	std::vector<std::string> paramVector;
	std::stringstream eventLineStream(foundation);
	//Put everything in a vector
	while (eventLineStream)
	{
		std::string s;
		if (!getline(eventLineStream, s, 'x')) break;
		paramVector.push_back(StringHelper::trim(s));
	}

	if (paramVector.size() == 2)
	{
		x = atoi(paramVector[0].c_str());
		y = atoi(paramVector[1].c_str());
	}
	else if (Config::hasAres && foundation == "Custom")
	{
		custom = true;
		section->readIntValue("Foundation.X", x, 1);
		section->readIntValue("Foundation.Y", y, 1);
	}
	else if (foundation == "3X3REFINERY") //lol, whenever it is actually used
	{
		x = 3;
		y = 3;
	}

}
