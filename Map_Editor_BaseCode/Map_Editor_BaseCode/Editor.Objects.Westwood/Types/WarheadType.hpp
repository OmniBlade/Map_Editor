#pragma once

#include "AbstractType.hpp"
#include "../Managers/WWList.hpp"

class WarheadType : public AbstractType
{
public:
	static WWList<WarheadType> Array;
	WarheadType(const std::string& id);

	void loadRules(INIFile* file) override;
	void loadArt(INIFile* file) override;

	std::string AnimList, DebrisTypes;


};

