#include "stdafx.h"
#include "SActionType.hpp"
#include "ParamCollection.hpp"
#include "ParamType.hpp"
#include "../../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../../Log.hpp"
#include <sstream>

SActionType::SActionType(INISection* section, ParamCollection* params)
{
	parse(section, params);
}

void SActionType::parse(INISection* section, ParamCollection* params)
{
	section->readIntValue("Identifier", identifier, atoi(section->getSectionName().c_str()));
	section->readStringValue("Name", name);
	section->readStringValue("Description", description);
	section->readStringValue("ParamString", paramString, "0");
	section->readBoolValue("RequiresAres", requiresAres, false);
	section->readBoolValue("Works", works, true);

	if (paramString == "0")
		return;

	LineSplitter split(paramString);
	if (split.pop(P1))
	{
		if (P1 > 0)
			param = params->get(P1);
	}
	else
	{
		Log::line("Unable to parse Action with ID '" + section->getSectionName() + "', invalid ParamString", Log::DEBUG);
	}

}

std::string SActionType::getNameWithParams()
{
	std::string ret = this->name;

	if (param && param->listIndex > 0)
	{
		/*
			Always 1 for ScriptType Actions, because there's only 1 possible Param :D
			Needs an overhaul anyway if ScriptType Actions ever support more than 1 param so no biggie
		*/
		std::string replacer = INameHelper::getReplacer(0x01); 

		std::size_t pos = ret.find(replacer);
		if (pos != std::string::npos)
		{
			std::string rep1 = ret.substr(0, pos);
			std::string rep2 = ret.substr(pos + 4, ret.size());

			ret = rep1 + param->name + rep2;
		}
	}
	return ret;
}
