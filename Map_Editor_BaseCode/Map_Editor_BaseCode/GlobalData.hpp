#pragma once

#include <string>
#include "FileSystem\INIFile\INISection.hpp"
class GlobalData
{
public:
	// [Main]
	static std::string MAIN_InstallDir;
	static std::string MAIN_BackSlash;
	static std::string MAIN_MissionDisk;
	static std::string MAIN_Expand;
	static std::string MAIN_Ecache;
	static std::string MAIN_Elocal;
	static bool MAIN_InGameLighting;
	static bool MAIN_FA2Mode;

	// [INI]
	static std::string INI_Rules;
	static std::string INI_Art;
	static std::string INI_Sound;
	static std::string INI_Eva;
	static std::string INI_Theme;
	static std::string INI_AI;
	static std::string INI_SP_Battle;
	static std::string INI_MP_Modes;
	static std::string INI_MP_Coop;

	// [Theaters]
	static std::map<std::string, INISection*> THEATER_Theaters;
};