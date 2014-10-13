#include "stdafx.h"
#include "House.hpp"
#include "../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../Editor.FileSystem/MapFile/WriterHelper.h"
#include "../../Log.hpp"
#include <sstream>

/* static */ MapObjectList<House> House::Array;

House::House(const std::string& id)
:ID(id)
{

}

void House::writeToINI(INIFile& file)
{
	if (Array.objectList.size() == 0)
	{
		Log::line("SECTION - Houses does not exist, will not write to map.", Log::DEBUG);
		return;
	}

	//Write section [Houses]
	std::stringstream number;
	int i = 0;
	for (auto& it : Array.objectList)
	{
		number << i;
		file.SetValue("Houses", number.str(), it->ID);
		++i;
		number.str(std::string());
		it->writeContentToINI(file);
	}
}

void House::writeContentToINI(INIFile& file)
{
	file.SetValue(ID.c_str(), "Country", Country);
	file.SetValue(ID.c_str(), "TechLevel", Log::toString(TechLevel));
	file.SetValue(ID.c_str(), "Credits", Log::toString(Credits));
	file.SetValue(ID.c_str(), "IQ", Log::toString(IQ));
	file.SetValue(ID.c_str(), "Edge", Edge);
	file.SetValue(ID.c_str(), "PlayerControl", WriterHelper::getBoolString(PlayerControl, WriterHelper::BoolType::YESNO));
	file.SetValue(ID.c_str(), "Color", Color);
	file.SetValue(ID.c_str(), "PercentBuilt", Log::toString(PercentBuilt));
	file.SetValue(ID.c_str(), "Allies", alliesAsString());

	std::stringstream number;
	if (NodeCount > 0)
	{
		file.SetValue(ID.c_str(), "NodeCount", Log::toString(NodeCount));
		for (int i = 0; i < NodeCount; ++i)
		{
			if (i < 10)
				number << '0';
			if (i < 100)
				number << '0';
			number << i;
			file.SetValue(ID.c_str(), number.str(), baseNodes[i]->asString());
			number.str(std::string());
		}
	}
}

void House::parse(INIFile* file, bool redundant)
{
	INISection* houseSection = file->getSection(ID);
	if (!houseSection) return;

	Name = ID;
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
		if (!node.empty())
		{
			LineSplitter split(node);

			std::string btype = split.pop_string();
			int x = split.pop_int();
			int y = split.pop_int();
			baseNodes.push_back(std::make_unique<BaseNode>(btype, x, y));

			node = "";
			number.str(std::string());
		}
		else
		{
			//Don't look for stuff that isn't there!
			break;
		}
	}
}

std::string House::alliesAsString()
{
	std::string ret;

	for (auto& it : Allies)
	{
		ret.append("," + it);
	}

	return ret.substr(1, ret.size());
}