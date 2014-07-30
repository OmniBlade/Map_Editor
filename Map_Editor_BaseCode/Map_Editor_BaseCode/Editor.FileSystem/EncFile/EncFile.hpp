#pragma once
#include <vector>

class BinaryReader;
struct FileProperties;

class EncFile
{
public:
	EncFile(const FileProperties& props, const std::string& fileName, bool asINI = true);
	
	/*
		Does a load for the loading
	*/
	void load(const std::string& fileName);

	/*
		Takes one to know one, after it found out it knows one, it'll unknow one and follow someone else on Twitter
	*/
	void gd();
	
	/*
		Walks to the end of the hallway, turns around three times and takes a shit in the gutter
	*/
	void gf();
	
	/*
		Known to cause destruction of processing units above the height of 45 meters under sea level
	*/ 
	void d();

private:
	bool asINI;
	BinaryReader* encReader;
	int el, fs;
	std::vector<char> fb, eb;
};

