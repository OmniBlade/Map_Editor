#pragma once

#include "../../Editor.FileSystem/IniFile/INIFile.hpp"

class SpecialWeapon
{
public:
	SpecialWeapon();
	void loadRules(INIFile* file);
};

