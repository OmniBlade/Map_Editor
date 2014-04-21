#pragma once

#include "../../Editor.FileSystem/IniFile/INIFile.hpp"

class AudioVisual
{
public:
	AudioVisual();
	void loadRules(INIFile* file);
};

