#pragma once

class INISection;

class Foundation
{
public:
	Foundation();
	void parse(INISection* section);
	~Foundation();

	bool custom = false;
	int x = 1;
	int y = 1;
};

