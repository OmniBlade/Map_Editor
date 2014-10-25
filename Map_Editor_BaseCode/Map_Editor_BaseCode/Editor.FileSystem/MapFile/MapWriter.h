#pragma once
#include <string>

class MapWriter
{
public:
	void writeAll(const std::string& fullFileName);
	void writeMap(const std::string& fullFileName);
	void writeNamesFile(const std::string& fullFileName);
	void setNamesFileName(const std::string& name) { namesFileName = name; };

private:
	std::string namesFileName, unstableMessage;
};

