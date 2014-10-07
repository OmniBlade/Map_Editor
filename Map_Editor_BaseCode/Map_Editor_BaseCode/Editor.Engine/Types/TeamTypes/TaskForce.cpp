#include "stdafx.h"
#include "TaskForce.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../../Log.hpp"

/* static */ MapObjectList<TaskForce> TaskForce::Array;

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

	/*
		If someone ever changes this limit...
		Counts from 0 - limit, thus 5 means 6 entries
	*/
	unsigned int taskForceLimit = 5;
	//unitList.reserve(taskForceLimit);
	//unitList.resize(taskForceLimit);

	for (unsigned int i = 0; i < taskForceLimit; ++i)
	{
		if (!section->checkKeyExistance(Log::toString(i)))
		{
			break; // Stop looking if an index is missing
		}
		else
		{
			unitList.push_back(std::make_unique<TFEntry>(section->getValue(Log::toString(i))));
		}
	}
}

void TaskForce::writeToINI(INIFile& file)
{
	std::stringstream number;
	int i = 0;
	for (auto& it : Array.objectTypeList)
	{
		if (!it->isGlobal)
		{
			number << i;
			file.SetValue("TaskForces", number.str(), it->ID);
			++i;
			number.str(std::string());
			it->writeContentToINI(file);
		}
	}
}

void TaskForce::writeContentToINI(INIFile& file)
{
	file.SetValue(ID.c_str(), "Name", Name);
	std::stringstream number;
	int i = 0;
	for (auto& it : this->unitList)
	{
		number << i;
		file.SetValue(ID.c_str(), number.str(), it->asString());
		++i;
		number.str(std::string());

		if (i == 6) //Only write 0 - 5!
			break;
	}
	file.SetValue(ID.c_str(), "Group", Log::toString(Group));
}