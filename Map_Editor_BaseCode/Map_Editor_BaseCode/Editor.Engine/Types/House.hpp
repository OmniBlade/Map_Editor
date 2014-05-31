#pragma once

#include "Managers/ObjectList.hpp"
#include <string>
#include <vector>
#include <memory>
#include "BaseNode.hpp"
#include "../../Editor.FileSystem/IniFile/INIFile.hpp"

class House
{
public:
	static ObjectList<House> Array;

	House(const std::string& id);

	void parse(INIFile* file, bool redundant);
	void loadAllies(const std::string& alliesList);
	void loadNodes(INISection* section);


	std::string ID;
	std::string Country;
	int TechLevel;
	int Credits; // x100 in-game
	int IQ;
	std::string Edge;
	bool PlayerControl;
	std::string Color;
	std::vector<std::string> Allies;
	int PercentBuilt;
	int NodeCount;
	std::vector<std::unique_ptr<BaseNode>> baseNodes;
};

