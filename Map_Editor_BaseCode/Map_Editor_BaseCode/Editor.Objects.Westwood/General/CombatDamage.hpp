#pragma once

#include "../../Editor.FileSystem/IniFile/INIFile.hpp"

class CombatDamage
{
public:
	CombatDamage();
	void loadRules(INIFile* file);
};

