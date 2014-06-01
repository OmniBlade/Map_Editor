#include "stdafx.h"
#include "VariableName.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"

/* static */ ObjectList<VariableName> VariableName::Array;

VariableName::VariableName()
{

}

void VariableName::parse(const std::string& id, const std::string& list)
{
	LineSplitter split(list);
	if (split.pop(name) && split.pop(state))
	{

	}
}

GlobalVariableName::GlobalVariableName(const std::string& name_)
{

}
