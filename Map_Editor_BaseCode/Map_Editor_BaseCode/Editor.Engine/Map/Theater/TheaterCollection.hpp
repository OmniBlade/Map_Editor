#pragma once

#include <vector>
#include <string>
#include <memory>
#include "../../../Editor.FileSystem/INIFile/INIFile.hpp"
#include "TheaterDefinition.hpp"

class TheaterCollection
{
public:
	static TheaterCollection* getInstance();
	
	/*
		Creates a list of all the theaters that need to be parsed
		Initially the configuration file is used to get the theater data,
		but the list is hardcoded
		
		@param _configFile The configuration file used for the mod / game
	*/ 
	void initiate(INIFile* _configFile);
	
	~TheaterCollection();

	/*
		When the theaters are initiated this function will parse them all
		Afterwards their presence and validity is validated
	*/
	void parseTheaters();
	
	/*
		Validates the presence of the theater specified in the parameter
		
		@param _theaterName The name of the theater to check the existance of
		@return True if the theater exists, false if it doesn't
	*/
	bool theaterExists(const std::string& _theaterName);
	
	/*
		Creates a theater with the specified name in the parameter
		Based on the name default values will be requested before creating a theater instance
		
		@param _theaterName The name of the theater
	*/
	void createTheater(const std::string& _theaterName);
	
	/*
		Validates the presence of every theater defined during the initialization
	*/
	void validateTheaterPresence();
	
	/*
		Gets the default values for the specified theater, note that this is completely hardcoded
		to Yuri's Revenge's defaults
		
		@param _theaterName The name of the theater whose default values are requested
		@return The list of default values for the theater
	*/
	std::vector<std::string> getDefaultValues(const std::string& _theaterName);

	/*
		Gets the currently used theater and returns a pointer to it
		@return Pointer to the theater
	*/
	TheaterDefinition* getCurrent();
	TheaterDefinition* getByININame(const std::string& name);
	/*
		Based on the given theater name in the parameter, the currently used theater is set
		@param theaterName The name of the theater that will be used
	*/
	void setCurrent(const std::string& theaterName);

private:
	static TheaterCollection* instance;
	TheaterCollection();
	TheaterDefinition* currentTheater = nullptr;
	std::vector<std::string> defTheaterNames;
	std::vector<std::unique_ptr<TheaterDefinition>> theaters;
	INIFile* configFile;
};

