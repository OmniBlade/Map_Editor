#include "stdafx.h"
#include "House.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../Log.hpp"
#include <sstream>

House::House(const std::string& id)
:ID(id)
{

}

void House::parse(INIFile* file)
{
	INISection* houseSection = file->getSection(ID);
	if (!houseSection) return;

	houseSection->readStringValue("Country", Country);
	houseSection->readIntValue("TechLevel", TechLevel);
	houseSection->readIntValue("Credits", Credits);
	houseSection->readIntValue("IQ", IQ);
	houseSection->readStringValue("Edge", Edge);
	houseSection->readBoolValue("PlayerControl", PlayerControl);
	houseSection->readStringValue("Color", Color);
	houseSection->readIntValue("PercentBuilt", PercentBuilt);
	houseSection->readIntValue("NodeCount", NodeCount);

	std::string allies_List;
	houseSection->readStringValue("Allies", allies_List);

	loadAllies(allies_List);
	loadNodes(houseSection);
}

void House::loadAllies(const std::string& alliesList)
{
	LineSplitter split(alliesList);
	for (unsigned int i = 0; i < split.size(); ++i)
	{
		Allies.push_back(split.pop_string());
	}
}

void House::loadNodes(INISection* section)
{
	std::string node;
	std::stringstream number;
	for (int i = 0; i < NodeCount; ++i)
	{
		if (i < 10)
			number << '0';
		if (i < 100)
			number << '0';
		number << i;

		section->readStringValue(number.str(), node);
		LineSplitter split(node);
		baseNodes.push_back(std::make_unique<BaseNode>(split.pop_string(), split.pop_int(), split.pop_int()));

		number.str(std::string());
	}
}