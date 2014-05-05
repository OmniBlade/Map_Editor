#pragma once

#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include <string>

class SpecialWeapon
{
public:
	SpecialWeapon();
	void loadRules(INIFile* file);

	std::string NukeWarhead;
	std::string NukeProjectile;
	std::string NukeDown;
	std::string MutateWarhead;
	std::string MutateExplosionWarhead;
	std::string EMPulseWarhead;	
	std::string EMPulseProjectile;
};

