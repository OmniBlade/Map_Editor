#pragma once

#include "AbstractType.hpp"
#include "../Managers/List.hpp"

class WarheadType : public AbstractType
{
public:
	static List<WarheadType> Array;
	WarheadType(const std::string& id);

	void loadRules(INIFile* file) override;
	void loadArt(INIFile* file) override;

	std::string AnimList, DebrisTypes;


};

