#pragma once

#include "../../Editor.FileSystem/IniFile/INIFile.hpp"
#include <string>

class AudioVisual
{
public:
	AudioVisual();
	void loadRules(INIFile* file);

	std::string DropPodPuff;
	std::string VeinAttack;
	std::string Dig;
	std::string AtmosphereEntry;
	std::string TreeFire;
	std::string OnFire;
	std::string Smoke;
	std::string SmallFire;
	std::string LargeFire;
};

