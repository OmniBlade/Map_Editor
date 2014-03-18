#include "stdafx.h"
#include "GlobalData.hpp"

// This is FIXED for Red Alert 2 and Yuri's Revenge. Only changed for TS/FS
unsigned int GlobalData::tileWidth = 60;
unsigned int GlobalData::tileHeight = 30;

// [MAIN]
std::string GlobalData::MAIN_EditorRoot = "D:\\Map_Editor_GIT\\Map_Editor\\Map_Editor_BaseCode\\Debug";
std::string GlobalData::MAIN_InstallDir = "";
std::string GlobalData::MAIN_BackSlash = "\\";
std::string GlobalData::MAIN_MissionDisk = "MD";
std::string GlobalData::MAIN_Expand = "EXPAND";
std::string GlobalData::MAIN_Ecache = "ECACHE";
std::string GlobalData::MAIN_Elocal = "ELOCAL";
bool GlobalData::MAIN_InGameLighting = true;
bool GlobalData::MAIN_FA2Mode = false;

// [INI]
std::string GlobalData::INI_Rules		= "RULESMD.INI";
std::string GlobalData::INI_Art			= "ARTMD.INI";
std::string GlobalData::INI_Sound		= "SOUNDMD.INI";
std::string GlobalData::INI_Eva			= "EVAMD.INI";
std::string GlobalData::INI_Theme		= "THEMEMD.INI";
std::string GlobalData::INI_AI			= "AIMD.INI";
std::string GlobalData::INI_SP_Battle	= "BATTLEMD.INI";
std::string GlobalData::INI_MP_Modes	= "MPMODESMD.INI";
std::string GlobalData::INI_MP_Coop		= "COOPCAMPMD.INI";

// [Theaters]
// Can't fill this until the file is parsed...
std::map<std::string, INISection*> GlobalData::THEATER_Theaters;