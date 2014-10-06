#pragma once
#include <string>
#include <fstream>

class MapWriter
{
public:
	void writeMap(const std::string& fullFileName);

	void writeMapMods();
	void writeBasicSections();
	void writeCoreSections();
	void writeTriggerSections();
	void writeAISections();
	void writeObjectSections();
	void writeDigest();

private:
	std::wofstream mapStream;

};

