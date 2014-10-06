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
	//Write section [Houses]
	std::stringstream number;
	int i = 0;
	for (auto& it : Array.objectTypeList)
	{
		number << i;
		file.SetValue("Houses", number.str(), it->ID);
		++i;
		number.str(std::string());
	}
	
	//Write each House
	for (auto& it : Array.objectTypeList)
	{
		if (!it->Country.empty())
			file.SetValue(it->ID.c_str(), "Country", it->Country);
		file.SetValue(it->ID.c_str(), "TechLevel", Log::toString(it->TechLevel));
		file.SetValue(it->ID.c_str(), "Credits", Log::toString(it->Credits));
		file.SetValue(it->ID.c_str(), "IQ", Log::toString(it->IQ));
		file.SetValue(it->ID.c_str(), "Edge", it->Edge);
		file.SetValue(it->ID.c_str(), "PlayerControl", WriterHelper::getBoolString(it->PlayerControl, WriterHelper::BoolType::YESNO));
		file.SetValue(it->ID.c_str(), "Color", it->Color);
		file.SetValue(it->ID.c_str(), "PercentBuilt", Log::toString(it->PercentBuilt));
		file.SetValue(it->ID.c_str(), "Allies", it->alliesAsString());
	
		if (it->NodeCount > 0)
		{
			file.SetValue(it->ID.c_str(), "NodeCount", Log::toString(it->NodeCount));
			for (int i = 0; i < it->NodeCount; ++i)
			{
				number << i;
				file.SetValue(it->ID.c_str(), number.str(), it->baseNodes[i]->asString());
				number.str(std::string());
			}
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
		LineSplitter split(node);

		std::string btype = split.pop_string();
		int x = split.pop_int();
		int y = split.pop_int();
		baseNodes.push_back(std::make_unique<BaseNode>(btype, x, y));
		
		node = "";
		number.str(std::string());
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