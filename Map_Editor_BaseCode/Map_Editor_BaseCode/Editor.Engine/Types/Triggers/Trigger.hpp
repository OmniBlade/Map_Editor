#pragma once

#include "../Managers/MapObjectList.hpp"
#include <string>

class Tag;
class Action;
class Event;
class Country;
class INIFile;

class Trigger
{
public:
	static MapObjectList<Trigger> Array;
	static void writeToINI(INIFile& file, bool flushNames = false);

	Trigger();
	void parse(const std::string& id, const std::string& list);
	void assignChild();
	void assignTag();
	std::string getUpperParentID();
	std::string getParentID();
	std::string asString(bool voidNames = false);

	bool isGlobal = false;
	std::string ID, Name, owner, child;
	bool Disabled;
	bool EasyEnabled;
	bool MedEnabled;
	bool HardEnabled;
	int Unknown;

	Country* pOwner;
	Trigger* pChild;
	Action* pAction;
	Event* pEvent;
	
	/*
		This is pure for faster Trigger nesting, unlike FA2 which
		cannot even resolve the Tag of a parent Trigger without first
		having to click on that Trigger...
	*/
	Tag* pTag; 


};

