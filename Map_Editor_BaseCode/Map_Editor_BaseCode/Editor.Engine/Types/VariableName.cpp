#include "stdafx.h"
#include "VariableName.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"

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

GlobalVariableName::GlobalVariableName()
{

}

void GlobalVariableName::parse(const std::string& id, const std::string& name_)
{
	ID = id;
	Name = name_;
}
