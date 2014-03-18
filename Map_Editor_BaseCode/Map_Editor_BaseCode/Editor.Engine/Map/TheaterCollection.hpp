#pragma once

#include <vector>
#include <string>
#include <memory>
#include "TheaterDefinition.hpp"
#include "../../Editor.FileSystem/INIFile/INIFile.hpp"

class TheaterCollection
{
public:
	TheaterCollection(INIFile* configFile = nullptr);
	~TheaterCollection();

	void parseTheaters();
	bool checkTheaterExistance(const std::string& _theaterName);
	void createTheater(const std::string& _theaterName = "");
	void validateTheaterPresence();
	std::vector<std::string> getDefaultValues(const std::string& _theaterName);

private:
	std::vector<std::string> defTheaterNames;
	std::vector<std::unique_ptr<TheaterDefinition>> theaters;
	INIFile* configFile;
};

