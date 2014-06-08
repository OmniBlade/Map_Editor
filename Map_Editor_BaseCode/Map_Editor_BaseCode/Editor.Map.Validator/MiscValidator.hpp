#pragma once
#include <string>

class Tube;

class MiscValidator
{
public:
	MiscValidator();
	~MiscValidator();

	void validateWaypoint();
	void validateLocals();
	void validateTube();
	void validateSmudge();

	std::string const& getOppositeTube(Tube* tube);
	void walkTubePath(Tube* tube);
};

