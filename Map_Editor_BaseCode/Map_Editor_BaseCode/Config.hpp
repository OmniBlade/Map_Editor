#pragma once

#include "Editor.FileSystem\IniFile\INIFile.hpp"
#include <string>

class Config
{
public:
	/*
		Parses the configuration file and puts the values in their respective variables
		Note: Some variables are not read from the file, but kept here for the sake of consistency
		They might be set through a command line
		
		@param file The config file to load
		@param name The name of the configuration file (passed on by the CONFIGS file)
		@param gameInstallDir The install directory of te game
	*/
	static void parse(INIFile* file, const std::string& name, const std::string& gameInstallDir);

	static unsigned int tileWidth;			// 
	static unsigned int tileHeight;			//
	static int language;					// Language of the game / text files
	static std::string editorRoot;			//
	static std::string configName;
	static bool enableDebug;				// Can we please get a debug file?
	static bool dumpTypes;
	static bool isSP;						// WHether this map is SP or MP, about 75% is MP, so default to false
	static std::string mapName;

	// [Main]
	static std::string installDir;			// Install directory of the game
	static std::string executable;
	static std::string backSlash;			// General back slash variable '\\'
	static std::string missionDisk;			// Suffix used for Yuri's Revenge, default is 'md' but some mods (Mental Omega) have this set to 'mo'
	static std::string expand;				// Name of the expandXX.mix files
	static std::string ecache;				// Name of the ecache*.mix files
	static std::string elocal;				// Name of the elocal*.mix files
	static bool inGameLighting;				// Whether to render in-game lighting over the overlay (or rather just TMPs)
	static bool FA2Mode;					// Disable any of the fancy elements and switch to antique mode
	static bool AIReferences;				// Whether to reference AI control file TeamTypes, TaskForces and ScriptTypes in the editor

	// [INI]
	static std::string rules;				// Name of the rules.ini file, default is 'rulesmd.ini', but some mods (MO again) have this set to 'rulesmo.ini'
	static std::string art;					// ditto, same for the rest of the files
	static std::string sound;
	static std::string eva;
	static std::string theme;
	static std::string AI;
	static std::string battle;
	static std::string modes;
	static std::string coop;

	// [GameExtension]
	static bool hasAres;
};