#pragma once
#include <vector>

class INISection;

class OverlayDataPack
{
public:
	OverlayDataPack(INISection* section);
	~OverlayDataPack();

	void read();

private:
	INISection* section;
};

