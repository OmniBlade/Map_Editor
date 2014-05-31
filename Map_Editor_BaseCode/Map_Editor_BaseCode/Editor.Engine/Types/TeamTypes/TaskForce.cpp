#include "stdafx.h"
#include "TaskForce.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../../Log.hpp"

/* static */ ObjectList<TaskForce> TaskForce::Array;

TaskForce::TaskForce(const std::string& id)
:ID(id)
{

}

void TaskForce::parse(INIFile* file, bool isGlobal_)
{
	INISection* section = file->getSection(ID);

	if (!section)
	{
		return;
	}

	isGlobal = isGlobal_;
	section->readStringValue("Name", Name);
	section->readIntValue("Group", Group);

	for (unsigned int i = 0; i < 5; ++i)
	{
		if (!section->checkKeyExistance(Log::toString(i)))
			break; // Stop looking if an index is missing
	}
}
