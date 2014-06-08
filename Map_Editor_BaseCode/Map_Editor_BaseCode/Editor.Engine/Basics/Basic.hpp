#pragma once
#include <string>

class Basic
{
public:
	
	static Basic* getBasic();
	void parse();

	std::string name, player;

private:
	static Basic* instance;
	Basic();

};

