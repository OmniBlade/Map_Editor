#include "stdafx.h"
#include "VariableName.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include <sstream>

/* static */ MapObjectList<VariableName> VariableName::Array;
/* static */ MapObjectList<GlobalVariableName> GlobalVariableName::Array;

VariableName::VariableName()
{

}

void VariableName::parse(const std::string& id, const std::string& list)
{
	ID = id;
	LineSplitter split(list);
	if (split.pop(Name) && split.pop(state))
	{

	}
}

void VariableName::writeToINI(INIFile& file, bool flushNames /* = false */)
{
	if (Array.objectList.size() == 0)
	{
		Log::line("SECTION - VariableNames does not exist, will not write to map.", Log::DEBUG);
		return;
	}

	for (auto& it : Array.objectList)
	{
		std::stringstream number;
		int i = 0;
		for (auto& it : Array.objectList)
		{
			if (!it->isGlobal)
			{
				number << i;
				file.SetValue("VariableNames", number.str(), it->asString(flushNames));
				++i;
				number.str(std::string());
			}
		}
	}
}

std::string VariableName::asString(bool voidName /* = false */)
{
	char buffer[512];

	sprintf_s(buffer, 512, "%s,%d",
		voidName ? "flush!" : this->Name.c_str(),
		this->state != 0,
		0
		);

	return buffer;
}

GlobalVariableName::GlobalVariableName()
{

}

void GlobalVariableName::parse(const std::string& id, const std::string& name_)
{
	ID = id;
	Name = name_;
}
