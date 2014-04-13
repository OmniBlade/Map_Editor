#pragma once

#include <vector>
#include <string>
#include <memory>
#include "TheaterDefinition.hpp"
#include "../../Editor.FileSystem/INIFile/INIFile.hpp"

class TheaterCollection
{
public:
	static TheaterCollection* getInstance();
	void initiate(INIFile* _configFile);
	
	~TheaterCollection();

	void parseTheaters();
	bool checkTheaterExistance(const std::string& _theaterName);
	void createTheater(const std::string& _theaterName = "");
	void validateTheaterPresence();
	std::vector<std::string> getDefaultValues(const std::string& _theaterName);

	TheaterDefinition* getCurrent();
	void setCurrent(const std::string& theaterName);

private:
	static TheaterCollection* instance;
	TheaterCollection();
	TheaterDefinition* currentTheater = nullptr;
	std::vector<std::string> defTheaterNames;
	std::vector<std::unique_ptr<TheaterDefinition>> theaters;
	INIFile* configFile;
};

