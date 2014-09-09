#include "stdafx.h"
#include "ParamType.hpp"
#include "../IniFile/LineSplitter.hpp"

ParamType::ParamType(int paramID_, const std::string& name_, int maxList)
:paramID(paramID_), name(name_)
{
	LineSplitter split(name_);

	split.pop(name);
	
	if (!split.empty())
	{
		split.pop(listIndex);

		/*  */
		if (listIndex < maxList || listIndex < 0)
			listIndex = 0;

	}
	else
	{
		listIndex = 0;
	}
}

