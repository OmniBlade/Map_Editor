#pragma once
#include <string>

/*
	OverlayType section is a hardcode fest
	Therefore it could be wise to validate the integrity and validity of the section
	and tell the user about the mistakes

	Safest thing to do is just to NEVER FUCK WITH THE LIST intensively and on a big scale
	Editing entry by entry is the safest way to go
*/

class OverlayTypeValidator
{
public:
	OverlayTypeValidator();

	void validateWalls();
	void validateTiberiums(); //Consecutive
	void validateBridges();	  //Consecutive
	void logHighBridgeError(int index);
	void logNonExisting(int index);
	void validateTracks();	  //Consecutive
	void validateVeinhole();
	void validateConsecutive(const std::string& name, int start, int end, int amount, bool isTiberium = false);
	void dumpOverlayTypes();

private:
	bool dumpItAll = false;
};

